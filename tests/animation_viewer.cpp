#include "KOK_Director.h"
#include "KOK_Model.h"
#include "KOK_Skeleton.h"
#include "shader.h"
#include "KOK_Camera.h"
#include "KOK_ParticleSystem.h"

#include "KOK_Imager.h"

#include <sstream>
#include <sys/timeb.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nanogui/nanogui.h>

#include "KOK_WindowManager.h"
#include "KOK_TextManager.h"
#include "KOK_TextConsole.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace nanogui;
using namespace KOK_Director;

#define SWITCH_TIMER 1.0f

//some color presets
const glm::vec3 K_COLOR_GREEN = glm::vec3(0.8f,1.0f,0.6f);
const glm::vec3 K_COLOR_RED = glm::vec3(1.0f, 0.7f, 0.7f);
const glm::vec3 K_COLOR_WHITE = glm::vec3(1.0f);
const glm::vec3 K_COLOR_BLACK = glm::vec3(0.0f);
#define K_COLOR_GREY glm::vec3(0.15f)

KOK_TextConsole * console = new KOK_TextConsole(48, 24);

double runTime;

int parseMemoryLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getMemoryValue()
{ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
		{
        if (strncmp(line, "VmRSS:", 6) == 0)
				{
            result = parseMemoryLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void GUIKeyCallback(GLFWwindow * w, int key, int scancode, int action, int mods)
{
	// If a key is pressed, toggle the relevant key-press flag
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_BACKSPACE:
			console->DeleteCharacter();
			break;
		case GLFW_KEY_ENTER:
			console->Return();
			break;
		default:
			// Do nothing...
			break;
		}
	}
}

void GUICharCallback(GLFWwindow *w, unsigned int codepoint)
{
	console->AddCharacter(codepoint);
}

int main()
{
	const GLuint WINDOW_WIDTH = 1280;
	const GLuint WINDOW_HEIGHT = 720;
	const std::string VERSION = "0.0 (test)";

	KOK_Camera * camera = new KOK_Camera(glm::vec3(-25.0f,0.0f,0.0f), glm::vec3(0.01f,0.0f,0.0f));

	//projection and model matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 100.0f);

	//start up opengl
	GLFWwindow * window;
	window = InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"KOK Animation Viewer", false);

	//setup all default shaders
	GLuint modelShader = 0;
	GLuint particleShader = 0;
	GLuint ssaoShader = 0;
	GLuint ppShader = 0;
	GLuint lightShader = 0;
	GLuint textFrameBuffer = 0;
	GLuint textRenderTexture = 0;
	//init gl and load shaders
	InitGL(WINDOW_WIDTH, WINDOW_HEIGHT, ssaoShader, ppShader, lightShader, modelShader, particleShader, textFrameBuffer, textRenderTexture);

	LightBuffer lightBuffer;
	ShadowData shadowData;
	InitLightBuffer(lightBuffer, shadowData, WINDOW_WIDTH, WINDOW_HEIGHT);

	float startTime = glfwGetTime();

  //time stamp for animation switch
  float switchStamp = 0.0f;

	//shark textures
	GLuint tex_shark_osh = LoadPNG("./Models/knight/textures/Paladin_OSH.png", false);
	GLuint tex_shark_diffuse = LoadPNG("./Models/knight/textures/Paladin_diffuse.png", true);
	GLuint tex_shark_n = LoadPNG("./Models/knight/textures/Paladin_normal.png", false);
	GLuint tex_brick_n = LoadPNG("./Textures/grimeTile_1_normal.png", false);
	GLuint tex_brick_o = LoadPNG("./Textures/grimeTile_1_OSR.png", false);
	GLuint tex_brick = LoadPNG("./Textures/grimeTile_1_diffuse.png", true);

	//quad meshes
	KOK_Mesh quadMesh = KOK_Model::GenerateQuad();
	KOK_Mesh * quad = &quadMesh;

	KOK_Model * ground = new KOK_Model("./Models/Test/skyBox.obj");
	ground->meshes[0].AddTexture(tex_brick);
	ground->meshes[0].AddTexture(tex_brick_n);
	ground->meshes[0].AddTexture(tex_brick_o);
	ground->meshes[0].SetTexScale(60);
	ground->SetPosition(glm::vec3(0,-2.5f,0));
	ground->SetScale(glm::vec3(100.0f));
	ground->SetStatic(true);

	KOK_Model * car = new KOK_Model("./Models/knight/Idle.fbx");
	car->SetEulerOrientation(0.0f,0.0f,-90.0f);
	car->meshes[0].AddTexture(tex_shark_diffuse);
	car->meshes[0].AddTexture(tex_shark_n);
	car->meshes[0].AddTexture(tex_shark_osh);
	car->SetPosition(glm::vec3(0.0f,-9.0f,0.0f));
	car->SetScale(glm::vec3(0.1f));



	//compute shader for skeleton transforms
	GLuint computeSkeletonShader = LoadComputeShader("./Shaders/skinnedTransform.glsl");

  //shark skeleton
  KOK_Skeleton shark_skeleton = KOK_Skeleton(car->meshes[0].GetMeshData(), computeSkeletonShader
   ,"./Models/knight/Idle.fbx", "idle");

  shark_skeleton.AddAnimation("./Models/knight/Walking.fbx", "walk");

	glfwSetKeyCallback(window, &GUIKeyCallback);
	glfwSetCharCallback(window, &GUICharCallback);

	KOK_TextManager * textManager = new KOK_TextManager("Fonts/DejaVuSans.ttf", WINDOW_WIDTH, WINDOW_HEIGHT);
	console->Print("test",K_COLOR_WHITE);
	console->Print("test",K_COLOR_WHITE);
	console->Print("testtttttttttttttttttttttttttttt",K_COLOR_WHITE);


	double nbTime = glfwGetTime();
	int nbFrames = 0;
	double currentFrames = 0.0;

	vector<KOK_PointLight*> pointLights;

	while(!glfwWindowShouldClose( window ) )
	{
		//calculate frame ms
		double currentTime = glfwGetTime();
		nbFrames++;
		if(currentTime - nbTime >= 0.1)
		{
			currentFrames = 100.0 / double(nbFrames);
			nbFrames = 0;
			nbTime += 0.1;
		}

		runTime = glfwGetTime() - startTime;


		//mouse position
		double posX;
		double posY;

		glfwGetCursorPos(window, &posX, &posY);


		//update shit
		glfwPollEvents();

		//draw shadows first
		//DrawShadows(shadowData, camera->Position()+glm::vec3(0,2,0));

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBindFramebuffer(GL_FRAMEBUFFER, lightBuffer.mapFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

		//glEnable(GL_STENCIL_TEST);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc (GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glCullFace(GL_CCW);
		glPolygonMode( GL_FRONT, GL_FILL );

		shark_skeleton.BoneTransform((float)runTime);

		glUseProgram(modelShader);

		car->Draw(modelShader, projection, camera->View());

		ground->Draw(modelShader, projection, camera->View());

		//draw shit
		glBindFramebuffer(GL_FRAMEBUFFER, lightBuffer.lightsFBO);
		glClear( GL_COLOR_BUFFER_BIT);
		glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

		DrawScreenQuad(quad, ssaoShader, ppShader, lightShader, shadowData, lightBuffer, pointLights, projection, camera->View(), camera->Position());

		//draw particle system./
		glUseProgram(particleShader);
		glEnable(GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc (GL_LEQUAL);

		if ( GLFW_PRESS == glfwGetKey( window, GLFW_KEY_ESCAPE ) )
		{
			glfwSetWindowShouldClose( window, 1 );
		}
		glDepthFunc (GL_ALWAYS);
		glDepthMask (GL_TRUE);
		glDisable (GL_CULL_FACE);
		//draw version
		stringstream ss;
		ss << currentFrames;
		string str = "Current MS per frame: " + ss.str();

		stringstream st;
		st << (float)(getMemoryValue()) / 1024.0f;
		string stt = "System Memory Usage: " + st.str() + "MB";

		textManager->DrawBox(520.0f, 570.0f, 520.0f, 160.0f, K_COLOR_GREY);
		textManager->DrawText("KOK ENGINE\nVERSION: " + VERSION,25.0f, 690.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(str, 25.0f, 620.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(stt, 25.0f, 590.0f, 0.5f, K_COLOR_WHITE);

		console->Draw(textManager, 1280, 0, K_COLOR_GREY);


		glfwSwapBuffers(window);
	}


	KillGL();
	return 0;
}

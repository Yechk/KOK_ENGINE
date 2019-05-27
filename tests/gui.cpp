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

#include "KOK_Message.h"
#include "KOK_Actor.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace KOK_Director;

#define SWITCH_TIMER 1.0f

//some color presets
const glm::vec3 K_COLOR_GREEN = glm::vec3(0.8f,1.0f,0.6f);
const glm::vec3 K_COLOR_RED = glm::vec3(1.0f, 0.7f, 0.7f);
const glm::vec3 K_COLOR_WHITE = glm::vec3(1.0f);
const glm::vec3 K_COLOR_BLACK = glm::vec3(0.0f);
#define K_COLOR_GREY glm::vec3(0.15f)
#define K_COLOR_GREY_LIGHT glm::vec3(0.25f)

double runTime;

//class to test actor. GUI class.
class MyGUI : public KOK_Actor
{
	void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender)
	{
		//prints message data

		if(subject == 0)
		{
			char derivedData[64];
			memcpy(&derivedData, data.p, 64);

			cout << "SUBJECT: " << subject << endl;
			cout << derivedData << endl;
		}

		//integer data
		if(subject == 1)
		{
			cout << "SUBJECT: " << subject << endl;
			cout << data.i << endl;
		}

		//float data
		if(subject == 2)
		{
			cout << "SUBJECT: " << subject << endl;
			cout << data.f << endl;
		}

		if(subject == 10)
		{
			cout << "slider value: " << data.ui << endl;
		}
	}

	void Update(double time)
	{

	}

	void Draw()
	{

	}
};

int main()
{
	const GLuint WINDOW_WIDTH = 1280;
	const GLuint WINDOW_HEIGHT = 720;
	const std::string VERSION = "0.0 (test)";

	KOK_Camera * camera = new KOK_Camera(glm::vec3(2.0f,0.5f,5.0f), glm::vec3(0.005f,0.0f,-0.01f));

	//gui actor
	MyGUI * gui = new MyGUI();

	char dd[] = "An urgent message. Should come first.";
	char ddd[64];

	strncpy(ddd, dd, 64);

	//post office for main messages
	KOK_PostOffice office = KOK_PostOffice(1024);

	MessageData tempData;

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

	GLuint cubeShader = LoadShaders("./Shaders/cubeVertex.vs","./Shaders/cubeFragment.fs");

	KOK_WindowManager windowTester;

	windowTester.InitGUI(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	InitWindowTextures();
	windowTester.CreateWindow(1280.0f, 360.0f, 512.0f, 360.0f, true, "Shader Tester");
	KOK_Actor * testLabel = windowTester.AddWidget("Shader Tester", "MOUSE POSITION:", LABEL, 2.0f, 0.0f, true);
	windowTester.AddWidget("Shader Tester", "Gloss", LABEL, 0.0f, 0.0f, true);
	KOK_Actor * testSlider = windowTester.AddWidget("Shader Tester", "MySlider", SLIDER, 1.0f, 0.0f, true);

	LightBuffer lightBuffer;
	ShadowData shadowData;
	InitLightBuffer(lightBuffer, shadowData, WINDOW_WIDTH, WINDOW_HEIGHT);

	float startTime = glfwGetTime();

  //time stamp for animation switch
  float switchStamp = 0.0f;

	//skybox texture
	KOK_SkyBox skyBox = KOK_SkyBox("./Textures/CubeMaps/Field/");


	//splash screen buffers
	GLuint splashBuffer0 = KOK_Imager::BlankPNG(1280, 720);
	GLuint splashBuffer1 = KOK_Imager::BlankPNG(1280, 720);

	//quad meshes
	KOK_Mesh quadMesh = KOK_Model::GenerateQuad();
	KOK_Mesh * quad = &quadMesh;

	KOK_Model * sphere0 = new KOK_Model("spider0");
	sphere0->SetPosition(glm::vec3(3.2f, -0.4f, -1.0f));
	sphere0->SetScale(glm::vec3(0.9f));
	sphere0->SetEulerOrientation(0.1f,-0.15, -0.5f);
	sphere0->SetStatic(true);


	KOK_TextManager * textManager = new KOK_TextManager("Fonts/DejaVuSans.ttf", WINDOW_WIDTH, WINDOW_HEIGHT);

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

		office.QueueMessage(5, 0, testSlider, testLabel, EXPRESS);


		//update shit
		glfwPollEvents();

		office.Update(MARCH);
		windowTester.UpdateGUI();

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

		glUseProgram(modelShader);

		sphere0->Draw(modelShader, projection, camera->View());

		float glossValue = (float)stoi(testLabel->label) / 100.0f;

		DrawScreenQuad(quad, ssaoShader, ppShader, lightShader, shadowData, lightBuffer, &skyBox, pointLights, projection, camera->View(), camera->Position(),
			glossValue, textManager);

		//draw particle system./
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(particleShader);
		glEnable(GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc (GL_LEQUAL);

		//put particles hereeeee

		//skybox
		//skyBox.Draw(cubeShader, projection, camera->View());

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

		//textManager->DrawSplash(1280.0f, 720.0f, splash_screen_test, splashBuffer0, splashBuffer1);
		//textManager->DrawBox(520.0f, 570.0f, 520.0f, 160.0f, K_COLOR_GREY_LIGHT);
		textManager->DrawText("KOK ENGINE\nVERSION: " + VERSION,25.0f, 690.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(str, 25.0f, 620.0f, 0.5f, K_COLOR_WHITE);

		windowTester.DrawGUI();


		glfwSwapBuffers(window);
	}


	KillGL();
	return 0;
}

#include "KOK_Director.h"
#include "KOK_Model.h"
#include "KOK_Skeleton.h"
#include "shader.h"
#include "KOK_Camera.h"
#include "KOK_Picker.h"
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

using namespace nanogui;
using namespace KOK_Director;

//some color presets
const glm::vec3 K_COLOR_GREEN = glm::vec3(0.8f,1.0f,0.6f);
const glm::vec3 K_COLOR_RED = glm::vec3(1.0f, 0.7f, 0.7f);
const glm::vec3 K_COLOR_WHITE = glm::vec3(1.0f);
const glm::vec3 K_COLOR_BLACK = glm::vec3(0.0f);
#define K_COLOR_GREY glm::vec3(0.15f)

int getMilliCount()
{
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int main()
{
	const GLuint WINDOW_WIDTH = 1920;
	const GLuint WINDOW_HEIGHT = 1080;
	const std::string VERSION = "0.0 (test)";

	bool picked = false;

	KOK_Camera * camera = new KOK_Camera(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0,0,0.001));
	int lastTime = 0;
	int deltaTime = 0;


	//ray picker
	KOK_Picker * picker = new KOK_Picker();

	//projection and model matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 100.0f);

	//start up opengl
	GLFWwindow * window;
	window = InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"KOK");

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

	Camera * fpsHandler = new Camera(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	lastTime = getMilliCount();
	float startTime = glfwGetTime();

	vector<KOK_PointLight*> pointLights;

	AddPointLight(pointLights, glm::vec3(0.5f,0.5f,0), 5.0f, 2, glm::vec3(1.0f), true);

	//gui for tweaking
	KOK_WindowManager * tweakManager = new KOK_WindowManager();
	tweakManager->InitGUI(window);
	tweakManager->SetFPSManager(fpsHandler);


	//texture of grate
	GLuint tex_Grate = LoadPNG("./Textures/grate_1.png", true);
	GLuint tex_Grass = LoadPNG("./Textures/grass.png", true);
	GLuint tex_white = LoadPNG("./Textures/white.png", true);
	GLuint tex_sky = LoadPNG("./Textures/SkyBoxA.png", true);
	GLuint tex_brick = LoadPNG("./Textures/grimeTile_1_diffuse.png", true);
	GLuint tex_particle_test = LoadPNG("./Textures/particle_test.png");
	GLuint tex_brick_n = LoadPNG("./Textures/grimeTile_1_normal.png", false);
	GLuint tex_brick_o = LoadPNG("./Textures/grimeTile_1_OSR.png", false);
	GLuint tex_blank_n = LoadPNG("./Textures/blank_n.png", false);
	GLuint tex_blank_osh = LoadPNG("./Textures/blank_osh.png", false);

	//shark textures
	GLuint tex_shark_osh = LoadPNG("./Textures/sharky/sharky_OSH.png", false);
	GLuint tex_shark_diffuse = LoadPNG("./Textures/sharky/sharky_BaseColor.png", true);
	GLuint tex_shark_n = LoadPNG("./Textures/sharky/sharky_Normal.png", false);

	//quad meshes
	KOK_Mesh quadMesh = KOK_Model::GenerateQuad();
	KOK_Mesh * quad = &quadMesh;

	//load ground
	KOK_Model * ground = new KOK_Model("./Models/Test/nicehills.obj");
	ground->meshes[0].AddTexture(tex_brick);
	ground->meshes[0].AddTexture(tex_brick_n);
	ground->meshes[0].AddTexture(tex_brick_o);
	ground->meshes[0].SetTexScale(60);
	ground->SetPosition(glm::vec3(0,-2.5f,0));
	ground->SetScale(glm::vec3(100.0f));
	ground->SetStatic(true);
	KOK_Model * car = new KOK_Model("./Models/sharky.dae");
	car->meshes[0].AddTexture(tex_shark_diffuse);
	car->meshes[0].AddTexture(tex_shark_n);
	car->meshes[0].AddTexture(tex_shark_osh);

	GLuint computeSkeletonShader = LoadComputeShader("./Shaders/skinnedTransform.glsl");

	//shark skeleton
	KOK_Skeleton shark_skeleton = KOK_Skeleton(car->_m_Scene, car->meshes[0].GetMeshData(), computeSkeletonShader);

	//random ass house
	KOK_Model * house = new KOK_Model("./Models/Test/architecture.obj");
	house->meshes[0].AddTexture(tex_white);
	house->meshes[0].AddTexture(tex_blank_n);
	house->meshes[0].AddTexture(tex_blank_osh);
	KOK_Model * skyBox = new KOK_Model("./Models/Test/skyBox.obj");
	skyBox->meshes[0].AddTexture(tex_sky);
	skyBox->meshes[0].AddTexture(tex_blank_n);
	skyBox->meshes[0].AddTexture(tex_blank_osh);

	//test particle particle system
	KOK_ParticleSystem particles(10000, tex_particle_test, 0.0, 100);

	KOK_TextManager * textManager = new KOK_TextManager("Fonts/DejaVuSans.ttf", WINDOW_WIDTH, WINDOW_HEIGHT);
	KOK_TextConsole * console = new KOK_TextConsole(48, 32);
	console->Print("test",K_COLOR_WHITE);
	console->Print("test",K_COLOR_WHITE);
	console->Print("testtttttttttttttttttttttttttttt",K_COLOR_WHITE);

	tweakManager->SetConsole(console);

	glm::vec3 spherePositions[20];
	for (int i = 0; i < 20; i++)
	{
		float randX = (rand() % 100) / 5;
		float randZ = (rand() % 100) / 5;
		spherePositions[i] = glm::vec3(randX-5,0.5f,randZ-3);
	}


	double nbTime = glfwGetTime();
	int nbFrames = 0;
	double currentFrames = 0.0;

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

		double runTime = glfwGetTime() - startTime;
		//car->BoneTransform(runTime);


		//mouse position
		double posX;
		double posY;

		glfwGetCursorPos(window, &posX, &posY);
		fpsHandler->lastX = posX;
    	fpsHandler->lastY = posY;

		//if(!fpsHandler->menuActive) glfwSetCursorPos(window, WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);

		//update shit
		glfwPollEvents();
		tweakManager->UpdateGUI();

		deltaTime = getMilliCount(); - lastTime;
		lastTime = getMilliCount();

		fpsHandler->move(deltaTime);
		camera->Position(fpsHandler->getPosition());
		camera->Target(fpsHandler->getRotation());
		camera->Update();

		pointLights[0]->SetPointLightInfo(true, tweakManager->radius, tweakManager->power, tweakManager->color);

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

		glUseProgram(modelShader);

		car->SetPosition(glm::vec3(3,0.5f,5));
		car->SetScale(glm::vec3(0.5f));
		shark_skeleton.BoneTransform((float)runTime);
		car->Draw(modelShader, projection, camera->View());

		ground->Draw(modelShader, projection, camera->View());

		house->SetPosition(glm::vec3(0,0,0));
		house->SetScale(glm::vec3(0.5f));
		//house->Draw(modelShader, projection, camera->View());

		skyBox->SetPosition(glm::vec3(0,0,0));
		skyBox->SetScale(glm::vec3(40.0f));
		skyBox->Draw(modelShader, projection, camera->View());
		//draw shit
		glBindFramebuffer(GL_FRAMEBUFFER, lightBuffer.lightsFBO);
		glClear( GL_COLOR_BUFFER_BIT);
		glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		//glUseProgram(defaultShader);


		//sphereModel->SetPosition(glm::vec3(0,0,-1));
		//sphereModel->SetScale(glm::vec3(1.0f));
		//sphereModel->Draw(defaultShader, projection, camera->view);

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		DrawScreenQuad(quad, ssaoShader, ppShader, lightShader, shadowData, lightBuffer, pointLights, projection, camera->View(), camera->Position());

		//draw particle system./
		glUseProgram(particleShader);
		glEnable(GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc (GL_LEQUAL);
		particles.Draw(particleShader, projection, camera->View(), runTime);

		if ( GLFW_PRESS == glfwGetKey( window, GLFW_KEY_ESCAPE ) )
		{
			glfwSetWindowShouldClose( window, 1 );
		}
		glDepthFunc (GL_ALWAYS);
		glDepthMask (GL_TRUE);
		glDisable(GL_CULL_FACE);
		//draw version
		stringstream ss;
		ss << currentFrames;
		string str = "Current MS per frame: " + ss.str();

		stringstream st;
		st << particles.ActiveParticles();
		string parts = "Number of particles: " + st.str();

		textManager->DrawText("KOK ENGINE\nVERSION: " + VERSION,25.0f, 1050.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(str, 25.0f, 980.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(parts, 25.0f, 910.0f, 0.5f, K_COLOR_WHITE);


		//tweakManager->DrawGUI();

		console->Draw(textManager, 1920, 312, K_COLOR_GREY);

		glfwGetCursorPos(window, &posX, &posY);
		fpsHandler->handleMouseMove(posX, posY);


		glfwSwapBuffers(window);
	}


	KillGL();
	return 0;
}

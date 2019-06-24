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

#define _DEBUG //tells phys x that this is a debug build. Switch to NDEBUG in a release

#include "PxPhysicsAPI.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "KOK_Message.h"
#include "KOK_Actor.h"

#include "stb_image.h"
#include "stb_image_resize.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define SWITCH_TIMER 1.0f

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049
using namespace KOK_Graphics;

#include "angelscript.h"
#include "scriptstdstring.h"
#include "scriptbuilder.h"

#include "KOK_Controller.h"

//TODO: create compile add ons seperately

//some color presets
const glm::vec3 K_COLOR_GREEN = glm::vec3(0.8f,1.0f,0.6f);
const glm::vec3 K_COLOR_RED = glm::vec3(1.0f, 0.7f, 0.7f);
const glm::vec3 K_COLOR_WHITE = glm::vec3(1.0f);
const glm::vec3 K_COLOR_BLACK = glm::vec3(0.0f);
#define K_COLOR_GREY glm::vec3(0.15f)
#define K_COLOR_GREY_LIGHT glm::vec3(0.25f)

double runTime;


int main()
{


	const GLuint WINDOW_WIDTH = 1280;
	const GLuint WINDOW_HEIGHT = 720;
	const std::string VERSION = "0.0 (test)";

	KOK_Camera * camera = new KOK_Camera(glm::vec3(10.0f,5.0f,10.0f), glm::vec3(0.0f,0.0f,0.0f));

	char dd[] = "An urgent message. Should come first.";
	char ddd[64];

	strncpy(ddd, dd, 64);

	//post office for main messages
	KOK_PostOffice office = KOK_PostOffice(1024);

	MessageData tempData;

	//////testing script controllers
	KOK_ScriptContext * scriptContext = new KOK_ScriptContext();
	KOK_ScriptedController myController = KOK_ScriptedController(scriptContext, &office, "test.as");

	//projection and model matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 100.0f);

	//start up opengl
	GLFWwindow * window;
	window = InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"KOK Animation Viewer",false);

	//setup all default shaders

	//init gl and load shaders
	InitGL();

	KOK_WindowManager windowTester;

	windowTester.InitGUI(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	InitWindowTextures();
	windowTester.CreateWindow(1280.0f, 360.0f, 512.0f, 360.0f, true, "Shader Tester");
	KOK_Actor * testLabel = windowTester.AddWidget("Shader Tester", "MOUSE POSITION:", LABEL, 2.0f, 0.0f, true);
	KOK_Actor * testLabel2 = windowTester.AddWidget("Shader Tester", "MOUSE POSITION:", LABEL, 2.0f, 1.0f, true);
	windowTester.AddWidget("Shader Tester", "Gloss", LABEL, 0.0f, 0.0f, true);
	windowTester.AddWidget("Shader Tester", "Specular", LABEL, 0.0f, 1.0f, true);
	KOK_Actor * testSlider = windowTester.AddWidget("Shader Tester", "MySlider", SLIDER, 1.0f, 0.0f, true);
	KOK_Actor * testSlider2 = windowTester.AddWidget("Shader Tester", "MySlider", SLIDER, 1.0f, 1.0f, true);

	//structs for holding FBO data
	TextProcessData * textData = new TextProcessData(WINDOW_WIDTH, WINDOW_HEIGHT);
	ParticleProcessData * particleData = new ParticleProcessData();

	KOK_RenderProcess * renderProcess = new KOK_RenderProcess(WINDOW_WIDTH, WINDOW_HEIGHT);

	//renderProcess->AddModel("belair", glm::vec3(2.5f, 0.5f, 1.5f), glm::vec3(0.5f), glm::vec3(0.1f,-0.05f, 0.0f), glm::vec3(0));
	renderProcess->AddModel("spider0", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0), glm::vec3(0));
	renderProcess->AddModel("cubefarm", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), glm::vec3(0), glm::vec3(0));

	float startTime = glfwGetTime();

  //time stamp for animation switch
  float switchStamp = 0.0f;

	//skybox texture
	KOK_SkyBox * skyBox = new KOK_SkyBox("./Textures/CubeMaps/Field/");


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
		office.QueueMessage(5, 0, testSlider2, testLabel2, EXPRESS);


		//update shit
		glfwPollEvents();

		office.Update(MARCH);
		windowTester.UpdateGUI();

		float glossValue = (float)stoi(testLabel->label) / 100.0f;
		float specValue = (float)stoi(testLabel2->label) / 100.0f;

		renderProcess->DrawScreenQuad(projection, camera, skyBox, glossValue, specValue);

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

		GLint total_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX,
		              &total_mem_kb);

		GLint cur_avail_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX,
		              &cur_avail_mem_kb);

		stringstream ssm;
		ssm << (total_mem_kb - cur_avail_mem_kb) / 1024;
		string strm = "GPU Memory Used: " + ssm.str() + "/2048MB";


		//textManager->DrawSplash(1280.0f, 720.0f, splash_screen_test, splashBuffer0, splashBuffer1);
		textManager->DrawBox(520.0f, 570.0f, 520.0f, 160.0f, K_COLOR_GREY_LIGHT);
		textManager->DrawText("KOK ENGINE\nVERSION: " + VERSION,25.0f, 690.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(str, 25.0f, 620.0f, 0.5f, K_COLOR_WHITE);
		textManager->DrawText(strm, 25.0, 580.0, 0.5f, K_COLOR_WHITE);

		//windowTester.DrawGUI();


		glfwSwapBuffers(window);
	}


	KillGL();
	return 0;
}

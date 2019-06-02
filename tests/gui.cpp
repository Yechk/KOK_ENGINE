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

#define SWITCH_TIMER 1.0f

using namespace KOK_Graphics;

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
	const GLuint WINDOW_WIDTH = 1920;
	const GLuint WINDOW_HEIGHT = 1080;
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
	window = InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"KOK Animation Viewer", true);

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

	renderProcess->AddModel("spider0", glm::vec3(3.2f, -0.5f, -1.0f), glm::vec3(0.9f), glm::vec3(0.1f,-0.15, -0.5f), glm::vec3(0));

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

		//textManager->DrawSplash(1280.0f, 720.0f, splash_screen_test, splashBuffer0, splashBuffer1);
		//textManager->DrawBox(520.0f, 570.0f, 520.0f, 160.0f, K_COLOR_GREY_LIGHT);
		//textManager->DrawText("KOK ENGINE\nVERSION: " + VERSION,25.0f, 690.0f, 0.5f, K_COLOR_WHITE);
		//textManager->DrawText(str, 25.0f, 620.0f, 0.5f, K_COLOR_WHITE);

		//windowTester.DrawGUI();


		glfwSwapBuffers(window);
	}


	KillGL();
	return 0;
}

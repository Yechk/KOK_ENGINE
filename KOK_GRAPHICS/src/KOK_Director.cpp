#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include "KOK_Director.h"
#include "KOK_Imager.h"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"


#include <stdio.h>
#include <iostream>
#include "KOK_Light.h"

#include <string>
using namespace std;

namespace KOK_Director
{

void InitGL(const int& width, const int& height, GLuint& ssaoShader, GLuint& ppShader, GLuint& lightShader, GLuint& modelShader,
	GLuint& particleShader, GLuint& textFrameBuffer, GLuint& textRenderTexture)
{
	//GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);

	//frame buffer for text overlay
	glGenFramebuffers(1, &textFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, textFrameBuffer);

	glGenTextures(1, &textRenderTexture);
	glBindTexture(GL_TEXTURE_2D, textRenderTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//all the shaders we neeed for the deferred pipeline
	ssaoShader = LoadShaders("./Shaders/quad.vs","./Shaders/pp_ssao.fs");
	ppShader = LoadShaders("./Shaders/quad.vs","./Shaders/quad.fs");
	lightShader = LoadShaders("./Shaders/quad.vs","./Shaders/pp_lights.fs");
	modelShader = LoadShaders("./Shaders/deferredShader.vs","./Shaders/deferredShader.fs");
	particleShader = LoadShaders("./Shaders/particleShader.vs", "./Shaders/particleShader.fs");

	glUseProgram(lightShader);
	GLuint uniformBlock = glGetUniformBlockIndex(lightShader, "lightData");
	glUniformBlockBinding(lightShader, uniformBlock, 2);
}

bool KillGL()
{
	glfwTerminate();
}

GLFWwindow* InitWindow(const int& width, const int& height, const char * name, bool fullScreen)
{
	if (!glfwInit())
	{
		fprintf (stderr, "Could Not Start GLFW3\n");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_SAMPLES, 1);
	glEnable(GL_MULTISAMPLE);

	int count;
	GLFWmonitor **monitors = glfwGetMonitors(&count);

	GLFWwindow * window;
	if(fullScreen) {window = glfwCreateWindow(width, height, name, monitors[0], NULL);}
	else {window = glfwCreateWindow(width, height, name, NULL, NULL);}
	if (!window)
	{
		fprintf(stderr, "Could Not Open Window!");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	return window;
}

void InitShadowData(ShadowData& shadowData, const GLuint& width, const GLuint& height)
{
	shadowData.shadowShader = LoadShaders("./Shaders/shadowDraw.vs","./Shaders/shadowDraw.fs");

	glGenFramebuffers(1, &shadowData.depthMapFBO);

	glGenTextures(1, &shadowData.depthMapTex);
	glBindTexture(GL_TEXTURE_2D, shadowData.depthMapTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowData.depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowData.depthMapTex, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shadowData.shadowWidth = width;
	shadowData.shadowHeight =  height;

	shadowData.shadowRange = 10.0f;
	glm::vec3 coord = glm::vec3(shadowData.shadowRange);

	shadowData.lightProjection = glm::ortho(-coord.x, coord.x, -coord.y, coord.y, -coord.z, coord.z);
}

bool InitLightBuffer(LightBuffer& lightBuffer, ShadowData& shadowData, const int& width, const int& height)
{
	GLuint gBuffer;
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	GLuint gPosition, gNormal, gColor, rBuffer, gEmissiveAmbient, gSpecularGloss, ssaoNormal, ssaoPosition, gDepth;

	// - position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	// - SSAO position color buffer
	glGenTextures(1, &ssaoPosition);
	glBindTexture(GL_TEXTURE_2D, ssaoPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, ssaoPosition, 0);

	// - normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	// - SSAO normal color buffer
	glGenTextures(1, &ssaoNormal);
	glBindTexture(GL_TEXTURE_2D, ssaoNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, ssaoNormal, 0);

	// - color + specular color buffer
	glGenTextures(1, &gColor);
	glBindTexture(GL_TEXTURE_2D, gColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColor, 0);

	//greyscale depth
	glGenTextures(1, &gDepth);
	glBindTexture(GL_TEXTURE_2D, gDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, gDepth, 0);

	// - emission ambient map
	glGenTextures(1, &gEmissiveAmbient);
	glBindTexture(GL_TEXTURE_2D, gEmissiveAmbient);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gEmissiveAmbient, 0);

	// - specularGloss map
	glGenTextures(1, &gSpecularGloss);
	glBindTexture(GL_TEXTURE_2D, gSpecularGloss);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, gSpecularGloss, 0);

	lightBuffer.mapFBO = gBuffer;
	lightBuffer.position = gPosition;
	lightBuffer.normal = gNormal;
	lightBuffer.color = gColor;
	lightBuffer.emissiveAmbient = gEmissiveAmbient;
	lightBuffer.specularGloss = gSpecularGloss;
	lightBuffer.ssaoNormal = ssaoNormal;
	lightBuffer.ssaoPosition = ssaoPosition;
	lightBuffer.tex_depth = gDepth;

	glGenRenderbuffers(1, &rBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, rBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	lightBuffer.renderBuffer = rBuffer;

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rBuffer);

	GLuint attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 , GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7};
	glDrawBuffers(8, attachments);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//create ssao frame buffer
	GLuint sBuffer;
	glGenFramebuffers(1, &sBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, sBuffer);
	GLuint sColor;

	// - color buffer for ssao
	glGenTextures(1, &sColor);
	glBindTexture(GL_TEXTURE_2D, sColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sColor, 0);

	lightBuffer.ssaoFBO = sBuffer;
	lightBuffer.ssaoColorBuffer = sColor;


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer for SSAO is not complete!" << endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//textures for light calculation
	GLuint lBuffer;
	glGenFramebuffers(1, &lBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, lBuffer);
	GLuint lColor, bColor;

	// - color buffer for lighting calculation (16F for HDR light data)
	glGenTextures(1, &lColor);
	glBindTexture(GL_TEXTURE_2D, lColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lColor, 0);

	//for first half of bloom
	glGenTextures(1, &bColor);
	glBindTexture(GL_TEXTURE_2D, bColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bColor, 0);

	lightBuffer.lightsFBO = lBuffer;
	lightBuffer.lightsColorBuffer = lColor;
	lightBuffer.bloomHColorBuffer = bColor;

	GLuint attachmentsN[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, attachmentsN);


	//glDrawBuffer(GL_COLOR_ATTACHMENT0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer for lights is not complete!" << endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	cout << "Light Color " << lColor << endl;
	cout << "SSAO Color " << sColor << endl;

	//uniform buffer for point light data
	glGenBuffers(1, &lightBuffer.lightUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer.lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 480, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER,0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 2, lightBuffer.lightUniformBuffer);

	//load cel texture
	bool success;
	lightBuffer.tex_cel = KOK_Imager::LoadPNG("./Textures/celMap.png", false, success);
	lightBuffer.tex_noise = KOK_Imager::LoadPNG("./Textures/noise.png", false, success);


	InitShadowData(shadowData, 2048, 2048);
}

void DrawShadows(ShadowData& shadowData, const glm::vec3& pos)
{
	float resX = 1.0f/shadowData.shadowWidth;
	float resY = 1.0f/shadowData.shadowHeight;
	glm::vec3 texelSize = glm::vec3(resX, 1.0f, resY);
	glm::vec3 snappedPos = floor(pos / texelSize) * texelSize;

  shadowData.lightView = glm::lookAt(snappedPos, snappedPos - glm::vec3(-1.01,0.7,0.1), glm::vec3(0,1,0));
	shadowData.lightSpaceMatrix = shadowData.lightProjection * shadowData.lightView;

	glViewport(0, 0, shadowData.shadowWidth, shadowData.shadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowData.depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glCullFace(GL_FRONT);

	glUseProgram(shadowData.shadowShader);
	SetUniformMat4(shadowData.shadowShader, "lightSpaceMatrix", shadowData.lightSpaceMatrix);
}

void DrawLights(const GLuint& shader, LightBuffer& lightBuffer, vector<KOK_PointLight*>& pointLights)
{
	//if(pointLights.size() == 0) return;

	GLuint numLights = glGetUniformLocation(shader, "numLights");

	glUniform1i(numLights, pointLights.size());
	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer.lightUniformBuffer);

	bool active;
	float radius;
	float power;
	glm::vec3 position;
	glm::vec3 color;

	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLights[i]->GetPointLightInfo(active, radius, power, color);
		position = pointLights[i]->Position();

	  if (!active) continue;
		int off = i * 48;
		glBufferSubData(GL_UNIFORM_BUFFER, off,      16, glm::value_ptr(glm::vec3(radius, power, 0.0f)));
		glBufferSubData(GL_UNIFORM_BUFFER, off + 16, 16, glm::value_ptr(position));
		glBufferSubData(GL_UNIFORM_BUFFER, off + 32, 16, glm::value_ptr(color));

	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void DrawScreenQuad(KOK_Mesh *quad, GLuint& ssaoShader, GLuint& ppShader, GLuint& lightShader, ShadowData& shadowData, LightBuffer& lightBuffer, KOK_SkyBox * cubeMap, vector<KOK_PointLight*>& pointLights,
	const glm::mat4& projection, const glm::mat4& view, const glm::vec3& camPosition, float testGloss, KOK_TextManager * tManager)
{
	//draw the lights first
	glUseProgram(lightShader);

	SetUniformTexture(lightShader,"gPosition", 0);
	SetUniformTexture(lightShader,"gNormal", 1);
	SetUniformTexture(lightShader,"gColor", 2);
	SetUniformTexture(lightShader,"gEmissiveAmbient", 3);
	SetUniformTexture(lightShader, "gSpecularGloss", 7);
	SetUniformTexture(lightShader, "irradiance", 8);
	SetUniformTexture(lightShader,"gCel", 4);
	SetUniformTexture(lightShader,"skyBox", 5);
	SetUniformTexture(lightShader,"shadowTex", 6);
	SetUniformVec3(lightShader, "viewPos", camPosition.x, camPosition.y, camPosition.z);
	SetUniformMat4(lightShader, "lightSpaceMatrix", shadowData.lightSpaceMatrix);

	SetUniformFloat(lightShader, "testGloss", testGloss);



	DrawLights(lightShader, lightBuffer, pointLights);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.position);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.normal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.color);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.emissiveAmbient);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.tex_cel);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetRadiance());
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetIrradiance());
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, shadowData.depthMapTex);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.specularGloss);

	quad->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//calculate ssao
	glBindFramebuffer(GL_FRAMEBUFFER, lightBuffer.ssaoFBO);
	glClear( GL_COLOR_BUFFER_BIT);

	glUseProgram(ssaoShader);


	SetUniformTexture(ssaoShader,"gNoise", 0);
	SetUniformTexture(ssaoShader,"ssaoPosition", 1);
	SetUniformTexture(ssaoShader,"ssaoNormal", 2);
	SetUniformMat4(ssaoShader, "projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.tex_noise);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.ssaoPosition);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.ssaoNormal);

	quad->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//calculate final process


	glUseProgram(ppShader);


	SetUniformTexture(ppShader,"tex_ssao", 0);
	SetUniformTexture(ppShader,"tex_lighting", 1);
	SetUniformTexture(ppShader,"tex_bloomH", 2);
	SetUniformTexture(ppShader,"tex_depth", 3);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.ssaoColorBuffer);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.lightsColorBuffer);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.bloomHColorBuffer);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, lightBuffer.tex_depth);

	quad->Draw();

}

void AddPointLight(vector<KOK_PointLight*>& pointLights, const glm::vec3& position, const float& radius, const GLuint& power, const glm::vec3& color, const bool& active)
{
	KOK_PointLight * light = new KOK_PointLight(position, radius, power, color, active);
	pointLights.push_back(light);
}
}

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

namespace KOK_Graphics
{

	void InitGL()
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

	void DrawScreenQuad(KOK_Mesh *quad, LightProcessData * lightData,
		DeferredLightingData * deferredData, SSAOData * ssaoData,
		ShadowData * shadowData, KOK_SkyBox * cubeMap, glm::mat4 projection,
		KOK_Camera * camera, KOK_TextManager * tManager,
		GLuint ppShader, GLuint cubeShader, AAProcessData * aaData)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, lightData->FBO);
		glClear( GL_COLOR_BUFFER_BIT );
		glViewport(0,0, lightData->screenWidth, lightData->screenHeight);

		//draw the lights first
		GLuint lightShader = lightData->shader;
		glm::vec3 camPosition = camera->GetPosition();
		glUseProgram(lightShader);

		SetUniformTexture(lightShader,"gPosition", 0);
		SetUniformTexture(lightShader,"gNormal", 1);
		SetUniformTexture(lightShader,"gColor", 2);
		SetUniformTexture(lightShader,"gEmissiveAmbient", 3);
		SetUniformTexture(lightShader, "gSpecularGloss", 4);
		SetUniformTexture(lightShader,"radiance", 5);
		SetUniformTexture(lightShader, "irradiance", 6);
		SetUniformTexture(lightShader,"shadowTex", 7);
		SetUniformVec3(lightShader, "viewPos", camPosition.x, camPosition.y, camPosition.z);
		SetUniformMat4(lightShader, "lightSpaceMatrix", shadowData->lightSpaceMatrix);



		lightData->DrawPointLights();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.position);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.normal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.color);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.emissiveAmbient);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.specularGloss);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetRadiance());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetIrradiance());
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, shadowData->depthMapTex);

		quad->Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//calculate ssao
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoData->FBO);
		glClear( GL_COLOR_BUFFER_BIT);

		GLuint ssaoShader = ssaoData->shader;
		glUseProgram(ssaoShader);


		SetUniformTexture(ssaoShader,"gNoise", 0);
		SetUniformTexture(ssaoShader,"ssaoPosition", 1);
		SetUniformTexture(ssaoShader,"ssaoNormal", 2);
		SetUniformMat4(ssaoShader, "projection", projection);
		SetUniformVec2(ssaoShader, "noiseScale", lightData->screenWidth, lightData->screenHeight);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ssaoData->noise);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.ssaoPosition);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.ssaoNormal);

		quad->Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//calculate final process

		if(aaData != NULL)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, aaData->FBO);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		glUseProgram(ppShader);


		SetUniformTexture(ppShader,"tex_ssao", 0);
		SetUniformTexture(ppShader,"tex_lighting", 1);
		SetUniformTexture(ppShader,"tex_bloomH", 2);
		SetUniformTexture(ppShader,"tex_depth", 3);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ssaoData->output);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, lightData->color);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, lightData->bloom);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, deferredData->textures.depth);

		quad->Draw();

		//draw particle system./
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glUseProgram(particleData->shader);
		glEnable(GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc (GL_LEQUAL);

		//put particles hereeeee

		//skybox
		cubeMap->Draw(cubeShader, projection, camera->GetView());

		if(aaData != NULL)
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, aaData->FBO);

			glReadBuffer(GL_COLOR_ATTACHMENT0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glBlitFramebuffer(0, 0, lightData->screenWidth, lightData->screenHeight, 0, 0,
				lightData->screenWidth, lightData->screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	}
}

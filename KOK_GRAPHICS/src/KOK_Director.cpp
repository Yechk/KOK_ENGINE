
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

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	bool KillGL()
	{
		glfwTerminate();
	}
//
	GLFWwindow* InitWindow(int width, int height, const char * name, bool fullScreen)
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

	void KOK_RenderProcess::DrawScreenQuad(glm::mat4 projection, KOK_Camera * camera, KOK_SkyBox * cubeMap, float glossTest, float specTest)
	{
		int screenWidth = _lightData.screenWidth;
		int screenHeight = _lightData.screenHeight;


		//draw models
		glBindFramebuffer(GL_FRAMEBUFFER, _deferredData.FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,screenWidth,screenHeight);

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc (GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glUseProgram(_deferredData.shader);

		//loop through models and draw
		for(GLuint i = 0; i < models.size(); i++)
		{
			models[i].Draw(_deferredData.shader, projection, camera->GetView());
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		DeferredLightingData::Textures textures = _deferredData.textures;

		//calculate ssao
		glBindFramebuffer(GL_FRAMEBUFFER, _ssaoData.FBO);
		glClear( GL_COLOR_BUFFER_BIT);

		GLuint ssaoShader = _ssaoData.shader;
		glUseProgram(ssaoShader);


		SetUniformTexture(ssaoShader,"gNoise", 0);
		SetUniformTexture(ssaoShader,"ssaoPosition", 1);
		SetUniformTexture(ssaoShader,"ssaoNormal", 2);
		SetUniformMat4(ssaoShader, "projection", projection);
		SetUniformVec2(ssaoShader, "noiseScale", screenWidth, screenHeight);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _ssaoData.noise);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures.ssaoPosition);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures.ssaoNormal);

		_quad.Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, _lightData.FBO);
		glClear( GL_COLOR_BUFFER_BIT );
		glViewport(0,0, screenWidth, screenHeight);

		//draw the lights
		GLuint lightShader = _lightData.shader;
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
		SetUniformTexture(lightShader,"tex_ssao", 8);
		SetUniformVec3(lightShader, "viewPos", camPosition.x, camPosition.y, camPosition.z);
		SetUniformMat4(lightShader, "lightSpaceMatrix", _shadowData.lightSpaceMatrix);

		SetUniformFloat(lightShader, "specTest", specTest);
		SetUniformFloat(lightShader, "glossTest", glossTest);



		_lightData.DrawPointLights();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures.position);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures.normal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures.color);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textures.emissiveAmbient);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textures.specularGloss);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetRadiance());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->GetIrradiance());
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, _shadowData.depthMapTex);
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, _ssaoData.output);

		_quad.Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//calculate final process

		glBindFramebuffer(GL_FRAMEBUFFER, _aaData.FBO);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_ppShader);


		SetUniformTexture(_ppShader,"tex_lighting", 0);
		SetUniformTexture(_ppShader,"tex_bloomH", 1);
		SetUniformTexture(_ppShader,"tex_depth", 2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _lightData.color);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _lightData.bloom);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures.depth);

		_quad.Draw();

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
		cubeMap->Draw(_skyBoxShader, projection, camera->GetView());

		_aaData.Draw();

	}
}

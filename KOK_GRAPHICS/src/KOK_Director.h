//Define The Initializer object header

#ifndef KOK_DIRECTOR_H
#define KOK_DIRECTOR_H

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "KOK_Mesh.h"
#include "KOK_Model.h"
#include "KOK_TextManager.h"
#include <vector>
#include "KOK_Light.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "KOK_Camera.h"
#include "KOK_Actor.h"

#include <string>
using namespace std;

namespace KOK_Graphics
{
	//this struct creates a process for anti-aliasing
	enum AATechnique
	{
		MSAA,
		SSAO
	};

	struct AAProcessData
	{
 		AATechnique technique = MSAA;

		GLuint FBO, RBO;           //frame buffer
		GLuint texture;       //texture for color attachment
		GLuint magnitude;     //holds # of samples for MSAA or scale of SSAA
		int screenWidth;
		int screenHeight;

		AAProcessData() {};

		//technique must be defined in constructor fo FBO creation
		AAProcessData(AATechnique t, GLuint m, int width, int height) : technique{t}, magnitude{m}
		{
			screenWidth = width;
			screenHeight = height;

			glGenFramebuffers(1, &FBO);
			glGenRenderbuffers(1, &RBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			glGenTextures(1, &texture);
			if(technique == MSAA)//texture and Framebuffer
			{
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m, GL_RGB, width, height, GL_TRUE);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);

				cout << "MSAA target created with " << m << " samples." << endl;

				glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m, GL_DEPTH24_STENCIL8, width, height);
		    glBindRenderbuffer(GL_RENDERBUFFER, 0);
		    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
			}

			//error checking
			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cout << "ERROR::FRAMEBUFFER:: Framebuffer for AA is not complete!" << endl;

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};

		void Draw()
		{
			if(technique == MSAA)
			{
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
				glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);

				//glReadBuffer(GL_COLOR_ATTACHMENT0);
				//glDrawBuffer(GL_COLOR_ATTACHMENT0);

				glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0,
					screenWidth, screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		};
	};

	struct SSAOData
	{
			GLuint shader;      //shader for SSAO calculations
			GLuint FBO;         //frame buffer

			GLuint output;      //calculated ssao output texture
			GLuint noise;       //noise texture for ssao

			SSAOData() {};

			SSAOData(int width, int height)
			{
				bool success = false;
				shader = LoadShaders("./Shaders/quad.vs","./Shaders/pp_ssao.fs");
				noise = LoadPNG("./Textures/noise.png", TEX_DEFAULT, success);

				//generate frame buffer and texture
				glGenFramebuffers(1, &FBO);
				glBindFramebuffer(GL_FRAMEBUFFER, FBO);

				// - color buffer for ssao
				glGenTextures(1, &output);
				glBindTexture(GL_TEXTURE_2D, output);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output, 0);


				if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					cout << "ERROR::FRAMEBUFFER:: Framebuffer for SSAO is not complete!" << endl;

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			};
	};

	struct LightProcessData
	{
		GLuint shader;        //final lighting calculations
		GLuint FBO;           //frame buffer

		GLuint color;         //stores the lighting levels
		GLuint bloom;         //stores bloom calculation

		GLuint plUniform;     //uniform buffer for point lights

		int screenWidth, screenHeight;

		vector<KOK_PointLight*> pointLights;

		LightProcessData() {};

		LightProcessData(int width, int height)
		{
			screenWidth = width;
			screenHeight = height;

			//load pp light shader
			shader = LoadShaders("./Shaders/quad.vs","./Shaders/pp_lights.fs");

			//Generate FBO and textures
			glGenFramebuffers(1, &FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			// - color buffer for lighting calculation (16F for HDR light data)
			glGenTextures(1, &color);
			glBindTexture(GL_TEXTURE_2D, color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

			//for first half of bloom
			glGenTextures(1, &bloom);
			glBindTexture(GL_TEXTURE_2D, bloom);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloom, 0);

			GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(2, attachments);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cout << "ERROR::FRAMEBUFFER:: Framebuffer for lights is not complete!" << endl;

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			//uniform buffer for point light data
			glGenBuffers(1, &plUniform);
			glBindBuffer(GL_UNIFORM_BUFFER, plUniform);
			glBufferData(GL_UNIFORM_BUFFER, 480, NULL, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER,0);

			glBindBufferBase(GL_UNIFORM_BUFFER, 2, plUniform);

			glUseProgram(shader);
			GLuint uniformBlock = glGetUniformBlockIndex(shader, "lightData");
			glUniformBlockBinding(shader, uniformBlock, 2);
		};

		void DrawPointLights()
		{
			GLuint numLights = glGetUniformLocation(shader, "numLights");

			glUniform1i(numLights, pointLights.size());
			glBindBuffer(GL_UNIFORM_BUFFER, plUniform);

			bool active;
			float radius;
			float power;
			glm::vec3 position;
			glm::vec3 color;

			for (int i = 0; i < pointLights.size(); i++)
			{
				pointLights[i]->GetPointLightInfo(active, radius, power, color);
				position = pointLights[i]->GetPosition();

			  if (!active) continue;
				int off = i * 48;
				glBufferSubData(GL_UNIFORM_BUFFER, off,      16, glm::value_ptr(glm::vec3(radius, power, 0.0f)));
				glBufferSubData(GL_UNIFORM_BUFFER, off + 16, 16, glm::value_ptr(position));
				glBufferSubData(GL_UNIFORM_BUFFER, off + 32, 16, glm::value_ptr(color));

			}
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		};

		void AddPointLight(glm::vec3 position, float radius, GLuint power, glm::vec3 color, bool active)
		{
			KOK_PointLight * light = new KOK_PointLight(position, radius, power, color, active);
			pointLights.push_back(light);
		};
	};

	struct TextProcessData
	{
		GLuint FBO, texture;       //frame buffer and render texture for drawing text

		TextProcessData(int width, int height)
		{
			glGenFramebuffers(1, &FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};
	};

	struct ParticleProcessData
	{
		GLuint shader;

		ParticleProcessData()
		{
			shader = LoadShaders("./Shaders/particleShader.vs", "./Shaders/particleShader.fs");
		};
	};

	struct DeferredLightingData
	{
			GLuint shader;      //shader for deferred lighting outputs
			GLuint FBO;         //frame buffer

			struct Textures     //stores textures from the mesh deferred shader
			{
				GLuint position,   //stores fragment positions
					normal,					 //stores fragment normals
					color,					 //stores albedo/diffuse
					emissiveAmbient, //
					specularGloss,   //
					depth,           //greyscale high precision depth
					ssaoNormal,      //normal calculation for SSAO
					ssaoPosition,    //fragment position for SSAO
					renderBuffer;    //main depth and stencil

			} textures;

			DeferredLightingData() {};

			DeferredLightingData(int width, int height)
			{
				//load deferredShader shader
				shader = LoadShaders("./Shaders/deferredShader.vs","./Shaders/deferredShader.fs");

				//generate frame buffer and textures
				glGenFramebuffers(1, &FBO);
				glBindFramebuffer(GL_FRAMEBUFFER, FBO);

				// - position buffer
				glGenTextures(1, &textures.position);
				glBindTexture(GL_TEXTURE_2D, textures.position);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures.position, 0);

				// - normal buffer
				glGenTextures(1, &textures.normal);
				glBindTexture(GL_TEXTURE_2D, textures.normal);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, textures.normal, 0);

				// - color buffer
				glGenTextures(1, &textures.color);
				glBindTexture(GL_TEXTURE_2D, textures.color);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, textures.color, 0);

				// - emission ambient map
				glGenTextures(1, &textures.emissiveAmbient);
				glBindTexture(GL_TEXTURE_2D, textures.emissiveAmbient);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, textures.emissiveAmbient, 0);

				// - SSAO position color buffer
				glGenTextures(1, &textures.ssaoPosition);
				glBindTexture(GL_TEXTURE_2D, textures.ssaoPosition);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, textures.ssaoPosition, 0);

				// - SSAO normal color buffer
				glGenTextures(1, &textures.ssaoNormal);
				glBindTexture(GL_TEXTURE_2D, textures.ssaoNormal);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, textures.ssaoNormal, 0);

				// - greyscale depth
				glGenTextures(1, &textures.depth);
				glBindTexture(GL_TEXTURE_2D, textures.depth);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, textures.depth, 0);

				// - specularGloss map
				glGenTextures(1, &textures.specularGloss);
				glBindTexture(GL_TEXTURE_2D, textures.specularGloss);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, textures.specularGloss, 0);

				glGenRenderbuffers(1, &textures.renderBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, textures.renderBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, textures.renderBuffer);

				GLuint attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 , GL_COLOR_ATTACHMENT3,
					GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7};
				glDrawBuffers(8, attachments);

				if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			};
	};

	struct ShadowData
	{
		GLuint shadowWidth;
		GLuint shadowHeight;

		GLuint depthMapFBO;
		GLuint depthMapTex;

		GLuint shadowShader;

		float shadowRange;

		glm::mat4 lightProjection;
		glm::mat4 lightView;
		glm::mat4 lightSpaceMatrix;

		ShadowData() {};

		ShadowData(int width, int height)
		{
			shadowShader = LoadShaders("./Shaders/shadowDraw.vs","./Shaders/shadowDraw.fs");

			glGenFramebuffers(1, &depthMapFBO);

			glGenTextures(1, &depthMapTex);
			glBindTexture(GL_TEXTURE_2D, depthMapTex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTex, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			shadowWidth = width;
			shadowHeight =  height;

			shadowRange = 10.0f;
			glm::vec3 coord = glm::vec3(shadowRange);

			lightProjection = glm::ortho(-coord.x, coord.x, -coord.y, coord.y, -coord.z, coord.z);

		};

		void Draw(glm::vec3 pos)
		{
			float resX = 1.0f/shadowWidth;
			float resY = 1.0f/shadowHeight;
			glm::vec3 texelSize = glm::vec3(resX, 1.0f, resY);
			glm::vec3 snappedPos = floor(pos / texelSize) * texelSize;

		  lightView = glm::lookAt(snappedPos, snappedPos - glm::vec3(-1.01,0.7,0.1), glm::vec3(0,1,0));
			lightSpaceMatrix = lightProjection * lightView;

			glViewport(0, 0, shadowWidth, shadowHeight);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc (GL_LESS);
			glCullFace(GL_FRONT);

			glUseProgram(shadowShader);
			SetUniformMat4(shadowShader, "lightSpaceMatrix", lightSpaceMatrix);

		};
	};


	void InitGL();
	bool KillGL();

	GLFWwindow* InitWindow(int width, int height, const char * name, bool fullScreen=true);

	class KOK_RenderProcess : public KOK_Actor
	{
	private:
		KOK_Mesh _quad;
		LightProcessData _lightData;
		DeferredLightingData _deferredData;
		SSAOData _ssaoData;
		ShadowData _shadowData;
		AAProcessData _aaData;

		GLuint _ppShader;
		GLuint _skyBoxShader;

		TextureLoadFlags _defaultTextureFlags;

		//vector to store all models to be drawn
		vector<KOK_Model> models;
//
	public:
		KOK_RenderProcess(int WINDOW_WIDTH, int WINDOW_HEIGHT) //default values
		{
			//structs for holding FBO data
			_lightData = LightProcessData(WINDOW_WIDTH, WINDOW_HEIGHT);
			_deferredData = DeferredLightingData(WINDOW_WIDTH, WINDOW_HEIGHT);
			_ssaoData = SSAOData(WINDOW_WIDTH, WINDOW_HEIGHT);
			_shadowData = ShadowData(WINDOW_WIDTH, WINDOW_HEIGHT);
			_aaData = AAProcessData(MSAA, 2, WINDOW_WIDTH, WINDOW_HEIGHT);

			_ppShader = LoadShaders("./Shaders/quad.vs","./Shaders/quad.fs");
			_skyBoxShader = LoadShaders("./Shaders/cubeVertex.vs","./Shaders/cubeFragment.fs");

			_quad = KOK_Model::GenerateQuad();

			_defaultTextureFlags = (TEX_DETAIL_LOW);
		}

		void Update(double time) {};
	  void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender) {};
	  void Draw() {};

		void DrawScreenQuad(glm::mat4 projection, KOK_Camera * camera, KOK_SkyBox * cubeMap, float glossTest, float specTest);

		KOK_Model * AddModel(string name)
		{
			models.push_back(KOK_Model(name, _defaultTextureFlags));
			return &models.back();
		}

		KOK_Model * AddModel(string name, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 rotation)
		{
			models.push_back(KOK_Model(name, position, scale, orientation, rotation, _defaultTextureFlags));
			return &models.back();
		}
	};

}

#endif //KOK_Director.h

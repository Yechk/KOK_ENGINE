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
#include "glm/gtc/matrix_transform.hpp"

#include <string>
using namespace std;

struct LightBuffer
{
	//frame buffers
	GLuint mapFBO, ssaoFBO, lightsFBO;
	//texture buffers
	GLuint position, normal, color, emissiveAmbient, specularGloss, renderBuffer, ssaoPosition, ssaoNormal, ssaoColorBuffer, lightsColorBuffer, bloomHColorBuffer, lightUniformBuffer,
		tex_cel, tex_noise, tex_depth;
};

struct ModelGroup
{
	vector<KOK_Model*> models;
	const char* name;
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
};

namespace KOK_Director
{
	void InitGL(const int& width, const int& height, GLuint& ssaoShader, GLuint& ppShader, GLuint& lightShader, GLuint& modelShader,
		GLuint& particleShader, GLuint& textFrameBuffer, GLuint& textRenderTexture);
	bool KillGL();

	GLFWwindow* InitWindow(const int& width, const int& height, const char * name, bool fullScreen=true);

	void InitShadowData(ShadowData& shadowData, const GLuint& width, const GLuint& height);
	bool InitLightBuffer(LightBuffer& lightBuffer, ShadowData& shadowData, const int& width, const int& height);

	void DrawShadows(ShadowData& shadowData, const glm::vec3& pos);

	void DrawLights(const GLuint& shader, LightBuffer& lightBuffer, vector<KOK_PointLight*>& pointLights);

	void DrawScreenQuad(KOK_Mesh *quad, GLuint& ssaoShader, GLuint& ppShader, GLuint& lightShader, ShadowData& shadowData, LightBuffer& lightBuffer, KOK_SkyBox * cubeMap,
		vector<KOK_PointLight*>& pointLights, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& camPosition, float testGloss, KOK_TextManager * tManager);

	void AddPointLight(vector<KOK_PointLight*>& pointLights, const glm::vec3& position, const float& radius, const GLuint& power, const glm::vec3& color, const bool& active);
}

#endif //KOK_Director.h

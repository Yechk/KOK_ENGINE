//kok model header
#ifndef KOK_MODEL_H
#define KOK_MODEL_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include "KOK_Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtx/quaternion.hpp>
using namespace std;

//class for model

class KOK_Model
{
public:
	KOK_Model();
	KOK_Model(string path);
	KOK_Model(KOK_Mesh mesh);
	KOK_Model(int divisions);
	void Draw(const GLuint& shader, const glm::mat4& projection, const glm::mat4& view);
	void DrawShadowPass(const GLuint& shader);

	void SetPosition(const glm::vec3& position);
	void SetScale(const glm::vec3& scale);
	void SetEulerRotation(const GLfloat& x, const GLfloat& y, const GLfloat& z);
	void SetEulerOrientation(const GLfloat& x, const GLfloat& y, const GLfloat& z);

	void SetStatic(bool isStatic);

	vector<KOK_Mesh> meshes;

	static KOK_Mesh GenerateQuad();

protected:
	void LoadModel(string path);
	KOK_Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
	void ProcessNode(aiNode * node, const aiScene * scene);
	static KOK_Mesh GeneratePlane(const GLint& divisions);

	string texturePath;

	void InitTransforms();

	glm::vec3 _position;
	glm::vec3 _scale;
	glm::quat _rotation;

	glm::quat _orientation;
};

#endif

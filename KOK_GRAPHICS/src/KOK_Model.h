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

#include "KOK_Actor.h"
#include "KOK_Imager.h"
using namespace std;

//class for model

namespace KOK_Graphics
{

	class KOK_Model : public KOK_Actor
	{
	public:
		KOK_Model();
		KOK_Model(string path, TextureLoadFlags defaultTextureFlags);
		KOK_Model(string path, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 rotation, TextureLoadFlags defaultTextureFlags);
		KOK_Model(KOK_Mesh mesh);
		KOK_Model(int divisions);
		void Draw() {};
		void Draw(GLuint shader, glm::mat4 projection, glm::mat4 view);
		void DrawShadowPass(GLuint shader);

		void Update(double time) {};
		void DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender) {};

		void SetPosition(glm::vec3 position);
		void SetScale(glm::vec3 scale);
		void SetEulerRotation(GLfloat x, GLfloat y, GLfloat z);
		void SetEulerOrientation(GLfloat x, GLfloat y, GLfloat z);

		void SetStatic(bool isStatic);

		vector<KOK_Mesh> meshes;

		static KOK_Mesh GenerateQuad();

	protected:
		void LoadModel(string path, TextureLoadFlags defaultTextureFlags);
		KOK_Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
		void ProcessNode(aiNode * node, const aiScene * scene);
		static KOK_Mesh GeneratePlane(GLint divisions);

		string texturePath;

		void InitTransforms();
		void InitTransforms(glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 rotation);

		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _rotation;

		glm::quat _orientation;

		TextureLoadFlags _defaultTextureFlags;
	};

}

#endif

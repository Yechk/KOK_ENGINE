//model c file
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "KOK_Mesh.h"
#include "KOK_Model.h"
#include "KOK_Imager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string.h>

#include <stdio.h>
#include <iostream>

using namespace std;

namespace KOK_Graphics
{

	KOK_Model::KOK_Model()
	{

	}

	void KOK_Model::InitTransforms()
	{
		_position = glm::vec3(0,0,0);
		_scale = glm::vec3(1.0f,1.0f,1.0f);
		_orientation = glm::toQuat( glm::orientate3( glm::vec3(0) ) );
		SetEulerRotation(0.0f,0.0f,0.0f);
	}

	void KOK_Model::InitTransforms(glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 rotation)
	{
		_position = position;
		_scale = scale;
		_orientation = glm::toQuat( glm::orientate3( orientation ) );
		SetEulerRotation(rotation.x, rotation.y, rotation.z);
	}

	void KOK_Model::SetStatic(bool isStatic)
	{
		for (GLint i = 0; i < meshes.size(); i++)
		{
			meshes[i].SetStatic(isStatic);
			meshes[i].ComputeModelMatrix(_position, _scale, _rotation*_orientation);
		}
	}

	KOK_Model::KOK_Model(string path, TextureLoadFlags defaultTextureFlags)
	{
		InitTransforms();
		LoadModel(path, defaultTextureFlags);
	}

	KOK_Model::KOK_Model(string path, glm::vec3 position, glm::vec3 scale, glm::vec3 orientation, glm::vec3 rotation, TextureLoadFlags defaultTextureFlags)
	{
		InitTransforms(position, scale, orientation, rotation);
		LoadModel(path, defaultTextureFlags);
	}

	KOK_Model::KOK_Model(KOK_Mesh mesh)
	{
		InitTransforms();
		meshes.push_back(mesh);
	}

	KOK_Model::KOK_Model(int divisions)
	{
		InitTransforms();
		meshes.push_back(GenerateQuad());
	}

	void KOK_Model::Draw(GLuint shader, glm::mat4 projection, glm::mat4 view)
	{
		for (GLuint i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw(shader, projection, view, _position, _scale, _rotation*_orientation);
		}
	}

	void KOK_Model::DrawShadowPass(GLuint shader)
	{
		for (GLuint i = 0; i < meshes.size(); i++)
		{
			meshes[i].DrawShadowPass(shader, _position, _scale, _rotation*_orientation);
		}
	}

	void KOK_Model::Update(double time)
	{

	};

	void KOK_Model::SetPosition(glm::vec3 position)
	{
		_position = position;
	}

	void KOK_Model::SetScale(glm::vec3 scale)
	{
		_scale = scale;
	}

	void KOK_Model::SetRotation(glm::quat q)
	{
		_rotation = q;
	}

	void KOK_Model::SetOrientation(glm::quat q)
	{
		_orientation = q;
	}

	void KOK_Model::SetEulerRotation(GLfloat x, GLfloat y, GLfloat z)
	{
		_rotation = glm::toQuat( glm::orientate3( glm::vec3(x, y, z) ) );
	}

	void KOK_Model::SetEulerOrientation(GLfloat x, GLfloat y, GLfloat z)
	{
		_orientation = glm::toQuat( glm::orientate3( glm::vec3(x, y, z) ) );
	}

	glm::vec3 KOK_Model::GetEulerRotation() const
	{
		return glm::eulerAngles(_rotation);
	}

	glm::quat KOK_Model::GetRotation() const
	{
		return _rotation;
	}

	KOK_Mesh KOK_Model::GenerateQuad()
	{
		vector<Vertex> vertices;
		vector<GLushort> indices;

		vertices.push_back(Vertex(glm::vec3(0.0f,1.0f,0.0f), glm::vec3(-1.0f,-1.0f,0.1f), glm::vec2(0.0f,0.0f)));
		vertices.push_back(Vertex(glm::vec3(0.0f,1.0f,0.0f), glm::vec3(1.0f,-1.0f,0.1f), glm::vec2(1.0f,0.0f)));
		vertices.push_back(Vertex(glm::vec3(0.0f,1.0f,0.0f), glm::vec3(1.0f,1.0f,0.1f), glm::vec2(1.0f,1.0f)));
		vertices.push_back(Vertex(glm::vec3(0.0f,1.0f,0.0f), glm::vec3(-1.0f,1.0f,0.1f), glm::vec2(0.0f,1.0f)));

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(2);
			indices.push_back(3);

		return KOK_Mesh(vertices, indices, glm::vec3(0), glm::vec3(0), glm::quat());
	}

	KOK_Mesh KOK_Model::GeneratePlane(GLint divisions)
	{
		vector<Vertex> vertices;
		vector<GLushort> indices;

		vertices.push_back(Vertex(glm::vec3(0.00f,1.0f,0.00f), glm::vec3(-1.0f,0.0f,-1.0f), glm::vec2(0.0f,0.0f)));
		vertices.push_back(Vertex(glm::vec3(0.00f,1.0f,0.00f), glm::vec3(1.0f,0.0f,-1.0f), glm::vec2(1.0f,0.0f)));
		vertices.push_back(Vertex(glm::vec3(0.00f,1.0f,0.00f), glm::vec3(1.0f,0.0f,1.0f), glm::vec2(1.0f,1.0f)));
		vertices.push_back(Vertex(glm::vec3(0.00f,1.0f,0.00f), glm::vec3(-1.0f,0.0f,1.0f), glm::vec2(0.0f,1.0f)));

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(2);
			indices.push_back(3);

		return KOK_Mesh(vertices, indices, glm::vec3(0), glm::vec3(0), glm::quat());
	}

	void KOK_Model::ProcessNode(aiNode * node, const aiScene * scene)
	{
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	KOK_Mesh KOK_Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
	{
		vector<Vertex> vertices;
		vector<GLushort> indices;

		for(GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoords = vec;
			}
			else
				vertex.texCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		//indices
		for(GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for(GLuint j = 0; j < face.mNumIndices; j++)
			    indices.push_back(face.mIndices[j]);

			//calculate tangents
			glm::vec3 deltaPos1 = vertices[face.mIndices[1]].position - vertices[face.mIndices[0]].position;
			glm::vec3 deltaPos2 = vertices[face.mIndices[2]].position - vertices[face.mIndices[0]].position;

			glm::vec2 deltaUV1 = vertices[face.mIndices[1]].texCoords - vertices[face.mIndices[0]].texCoords;
			glm::vec2 deltaUV2 = vertices[face.mIndices[2]].texCoords - vertices[face.mIndices[0]].texCoords;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		  glm::vec3 tangent;

			tangent.x = r * (deltaUV2.y * deltaPos1.x - deltaUV1.y * deltaPos2.x);
			tangent.y = r * (deltaUV2.y * deltaPos1.y - deltaUV1.y * deltaPos2.y);
			tangent.z = r * (deltaUV2.y * deltaPos1.z - deltaUV1.y * deltaPos2.z);
		  //glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
			tangent = normalize(tangent);
			vertices[face.mIndices[0]].tangent = tangent;
			vertices[face.mIndices[1]].tangent = tangent;
			vertices[face.mIndices[2]].tangent = tangent;
		}


		//load textures or set default for missing textures
		bool success = false;

		//diffuse
		GLuint diffuse = LoadPNG(texturePath + "Diffuse.png", _defaultTextureFlags, success);

		//normal
		GLuint normal = LoadPNG(texturePath + "Normal.png", _defaultTextureFlags, success);

		//emissiveAmbient
		GLuint emissiveAmbient = LoadPNG(texturePath + "EmissiveAmbient.png", _defaultTextureFlags, success);

		//specularGloss
		GLuint specularGloss = LoadPNG(texturePath + "SpecularGloss.png", _defaultTextureFlags, success);

		KOK_Mesh newMesh = KOK_Mesh(vertices, indices, _position, _scale, _rotation * _orientation);
		newMesh.SetMeshTextures(diffuse, normal, emissiveAmbient, specularGloss);

		return newMesh;
	}

	void KOK_Model::LoadModel(string path, TextureLoadFlags defaultTextureFlags)
	{
		_defaultTextureFlags = defaultTextureFlags;

		//path for model
		string basePath = "./Models/" + path + "/";
		string modelPath = basePath + path;

		texturePath = basePath + "default/" + path + "_";

		Assimp::Importer import;
		const aiScene * _m_Scene;
		_m_Scene = import.ReadFile(modelPath + ".obj", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeGraph);

		if(!_m_Scene || _m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_m_Scene->mRootNode)
		{
			_m_Scene = import.ReadFile(modelPath + ".fbx", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeGraph);
			if(!_m_Scene || _m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_m_Scene->mRootNode)
			{
				cout << "ERROR WITH ASSIMP::" << import.GetErrorString() << endl;
				return;
			}
		}

		ProcessNode(_m_Scene->mRootNode, _m_Scene);
	}

}

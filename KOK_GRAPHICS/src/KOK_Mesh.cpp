//KOK Mesh
using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "KOK_Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "KOK_Imager.h"

namespace KOK_Graphics
{

	KOK_Mesh::KOK_Mesh(vector<Vertex>& vertices, vector<GLushort>& indices, glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	{
		SetupMesh(vertices, indices);
		_isStatic = false;
		ComputeModelMatrix(position, scale, rotation);
	}

	KOK_Mesh::KOK_Mesh()
	{

	}

	void KOK_Mesh::SetupMesh(vector<Vertex>& vertices, vector<GLushort>& indices)
	{
		_meshData._vertices = vertices;
		_meshData._indices = indices;

		_meshData._texScale = 1.0f;

		glGenVertexArrays(1, &_meshData._VAO);
		glGenBuffers(1, &_meshData._VBO);
		glGenBuffers(1, &_meshData._EBO);

		glBindVertexArray(_meshData._VAO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _meshData._VBO);

		glBufferData(GL_SHADER_STORAGE_BUFFER, _meshData._vertices.size() * sizeof(Vertex), &_meshData._vertices[0], GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, _meshData._VBO); // Buffer Binding 0

		glBindBuffer(GL_ARRAY_BUFFER, _meshData._VBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshData._EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _meshData._indices.size() * sizeof(GLushort), &_meshData._indices[0], GL_STATIC_DRAW);

		//vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		//vertex coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
		//tangents
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

		glBindVertexArray(0);
	}

	void KOK_Mesh::ComputeModelMatrix(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	{
		_MD = glm::mat4(1.0f) * glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
	}

	void KOK_Mesh::SetShaderProperties(GLuint shader, glm::mat4 projection, glm::mat4 view, glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	{
		//set shader properties here
		_MV = view * _MD;
		SetUniformMat4(shader, "MVP", projection*_MV);
		SetUniformMat4(shader, "MV", _MV);
		SetUniformMat4(shader, "M", _MD);

		SetUniformFloat(shader, "texScale", _meshData._texScale);

		SetUniformTexture(shader,"diffuseTex", 0);
		SetUniformTexture(shader, "normalTex", 1);
		SetUniformTexture(shader, "emissiveAmbientTex", 2);
		SetUniformTexture(shader, "specularGlossTex", 3);
	}

	void KOK_Mesh::BindDrawTex()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _meshData.diffuse);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _meshData.normal);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _meshData.emissiveAmbient);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _meshData.specularGloss);
	}

	void KOK_Mesh::Draw(GLuint shader, glm::mat4 projection, glm::mat4 view, glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	{
		if(!_isStatic) ComputeModelMatrix(position, scale, rotation);

		SetShaderProperties(shader, projection, view, position, scale, rotation);

		BindDrawTex();

		Draw();
	}

	void KOK_Mesh::Draw()
	{
		glBindVertexArray(_meshData._VAO);
		glDrawElements(GL_TRIANGLES, _meshData._indices.size(), GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}

	void KOK_Mesh::DrawShadowPass(GLuint shader, glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	{
		if(!_isStatic) ComputeModelMatrix(position, scale, rotation);
		SetUniformMat4(shader, "M", _MD);

		Draw();
	}

	void KOK_Mesh::SetTexScale(float scale)
	{
		_meshData._texScale = scale;
	}

	KOK_SkyBox::KOK_SkyBox(string path)
	{
		LoadEnvironment(path, _texture, _irradiance, _radiance);

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		//glGenBuffers(1, &_EBO);

		glBindVertexArray(_VAO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _VBO);

		glBufferData(GL_SHADER_STORAGE_BUFFER, 108 * sizeof(float), &_vertices[0], GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, _VBO); // Buffer Binding 0

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

		//vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

		glBindVertexArray(0);
	}

	void KOK_SkyBox::Draw(GLuint shader, glm::mat4 projection, glm::mat4 view)
	{
		glUseProgram(shader);

		//glm::quat rotation = glm::toQuat( glm::orientate3( glm::vec3(0.0f, 0.0f, -3.14159f/2.0f) ) );

		//glm::mat4 MD = glm::mat4(1.0f) * glm::scale(glm::vec3(1.0f));
		glm::mat4 MVP = projection * glm::mat4(glm::mat3(view));
		SetUniformMat4(shader, "MVP", MVP);
		SetUniformTexture(shader,"diffuseTex", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

}

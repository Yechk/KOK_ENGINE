//mesh class
#ifndef KOK_MESH_H
#define KOK_MESH_H

#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.h"
#include <glm/gtx/quaternion.hpp>

//definitions for vertex and texture
struct Vertex
{
	glm::vec3 transPosition;
	GLfloat pad0;
	glm::vec3 position;
	GLfloat pad1;
	glm::vec3 normal;
	GLfloat pad2;
	glm::vec2 texCoords;
	GLfloat pad3 [2];
	glm::vec3 tangent;
	GLfloat pad4;

	Vertex(const glm::vec3& norm, const glm::vec3& pos, const glm::vec2& tex) : transPosition{pos}, position{pos}, normal{norm}, texCoords{tex} {};
	Vertex() {};
};

struct MeshData
{
	//mesh data
	vector<Vertex> _vertices;
	vector<GLuint> _indices;
	GLuint diffuse;
	GLuint normal;
	GLuint emissiveAmbient;
	GLuint specularGloss;

	GLuint _VAO, _VBO, _EBO;
	float _texScale;

	MeshData() {};
};

//class for kok mesh
class KOK_Mesh
{
public:

	//functions
	KOK_Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);
	KOK_Mesh();
	void BindDrawTex();
	void ComputeModelMatrix(const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);
	void Draw(const GLuint& shader, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);
	void Draw();
	void DrawShadowPass(const GLuint& shader, const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);

	void SetShaderProperties(const GLuint& shader, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);
	void SetupMesh(const vector<Vertex>& vertices, const vector<GLuint>& indices);
	void SetTexScale(const float& scale);

	MeshData * GetMeshData();
	inline void SetMeshTextures(GLuint diffuse, GLuint normal, GLuint emissiveAmbient, GLuint specularGloss)
	{
		_meshData.diffuse = diffuse;
		_meshData.normal = normal;
		_meshData.emissiveAmbient = emissiveAmbient;
		_meshData.specularGloss = specularGloss;
	};

	inline void SetStatic(bool isStatic) { _isStatic = isStatic; }
protected:

	bool _isStatic;

	glm::mat4 _MV;
	glm::mat4 _MD;

	MeshData _meshData;
};
//

class KOK_SkyBox
{
private:
	float _vertices[108] = {
		// positions
		        -1.0f,  1.0f, -1.0f,
		        -1.0f, -1.0f, -1.0f,
		         1.0f, -1.0f, -1.0f,
		         1.0f, -1.0f, -1.0f,
		         1.0f,  1.0f, -1.0f,
		        -1.0f,  1.0f, -1.0f,

		        -1.0f, -1.0f,  1.0f,
		        -1.0f, -1.0f, -1.0f,
		        -1.0f,  1.0f, -1.0f,
		        -1.0f,  1.0f, -1.0f,
		        -1.0f,  1.0f,  1.0f,
		        -1.0f, -1.0f,  1.0f,

		         1.0f, -1.0f, -1.0f,
		         1.0f, -1.0f,  1.0f,
		         1.0f,  1.0f,  1.0f,
		         1.0f,  1.0f,  1.0f,
		         1.0f,  1.0f, -1.0f,
		         1.0f, -1.0f, -1.0f,

		        -1.0f, -1.0f,  1.0f,
		        -1.0f,  1.0f,  1.0f,
		         1.0f,  1.0f,  1.0f,
		         1.0f,  1.0f,  1.0f,
		         1.0f, -1.0f,  1.0f,
		        -1.0f, -1.0f,  1.0f,

		        -1.0f,  1.0f, -1.0f,
		         1.0f,  1.0f, -1.0f,
		         1.0f,  1.0f,  1.0f,
		         1.0f,  1.0f,  1.0f,
		        -1.0f,  1.0f,  1.0f,
		        -1.0f,  1.0f, -1.0f,

		        -1.0f, -1.0f, -1.0f,
		        -1.0f, -1.0f,  1.0f,
		         1.0f, -1.0f, -1.0f,
		         1.0f, -1.0f, -1.0f,
		        -1.0f, -1.0f,  1.0f,
		         1.0f, -1.0f,  1.0f
	};
	GLuint _indices[36] = {
		1,4,3,
		6,7,8,
		2,6,5,
		3,7,6,
		3,4,8,
		8,4,1,
		2,1,3,
		5,6,8,
		1,2,5,
		2,3,6,
		7,3,8,
		5,8,1
	};

	GLuint _texture;
	GLuint _radiance;
	GLuint _irradiance;
	GLuint _VAO, _VBO, _EBO;

public:
	KOK_SkyBox(string path);

	inline GLuint GetTexture() {return _texture;};
	inline GLuint GetRadiance() {return _radiance;};
	inline GLuint GetIrradiance() {return _irradiance;};

	void Draw(const GLuint& shader, const glm::mat4& projection, const glm::mat4& view);
};

#endif

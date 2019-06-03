#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
using namespace std;

#include <glm/glm.hpp>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

GLuint LoadComputeShader(const char * path);

void SetUniformMat4(GLuint shader, const string &name,const glm::mat4 & mat);

void SetUniformTexture(GLuint shader,const std::string &name,GLuint tex);

void SetUniformBool(GLuint shader, const string &name, bool value);

void SetUniformFloat(GLuint shader, const string &name, float value);

void SetUniformVec3(GLuint shader, const string &name, float x, float y, float z);

void SetUniformVec4(GLuint shader, const string &name, float x, float y, float z, float w);

void SetUniformVec2(GLuint shader, const string &name, float x, float y);

//a class for post processing effects
class PostEffect
{

};

#endif

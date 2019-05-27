#ifndef KOK_BLOK_H
#define KOK_BLOK_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;

class KOK_Blok
{
  union Mem_Blok_Standard
  {
    GLint mem_int;
    GLuint mem_uint;
    GLfloat mem_float;
    bool mem_bool;
  };

  union Mem_Blok_GLM
  {
    glm::vec2 mem_vec2;
    glm::vec3 mem_vec3;
    glm::mat3 mem_mat3;
    glm::mat4 mem_mat4;
  };

  const static GLuint BLOCKSIZE = 512;
  const static GLuint STANDARDSIZE = BLOCKSIZE / sizeof(Mem_Blok_Standard);
  const static GLuint GLMSIZE = BLOCKSIZE / sizeof(Mem_Blok_GLM);

  static Mem_Blok_Standard sBlok[STANDARDSIZE];
  static Mem_Blok_GLM gBlok[GLMSIZE];

  KOK_Blok()
  {
  }
};

#endif

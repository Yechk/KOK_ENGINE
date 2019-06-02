#ifndef KOK_IMAGER_H
#define KOK_IMAGER_H

#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stdio.h"
#include <iostream>

namespace KOK_Imager
{

GLuint LoadPNG(string path, bool gamma, bool compress, bool &success);

void LoadCubeMap(string path, string sidesNames[6], GLuint lod, GLuint cubeMap, bool usesMips);
void LoadEnvironment(string path, GLuint& sky, GLuint& irradiance, GLuint& radiance);

GLuint BlankPNG(GLuint width, GLuint height);
GLuint BlankPNG16(GLuint width, GLuint height);

struct DefaultTexture
{
  GLuint texture;

  DefaultTexture()
  {
    bool success = false;

    texture = LoadPNG("../Textures/Default/diffuse.png", false, true, success);
    cout << "DEFAULT LOADED: " << success << endl;

  };

  ~DefaultTexture()
  {
    glDeleteTextures(1, &texture);
  }

};


};

#endif

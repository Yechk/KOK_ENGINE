#ifndef KOK_IMAGER_H
#define KOK_IMAGER_H

#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stdio.h"
#include <iostream>

#include "stb_image.h"
#include "stb_image_resize.h"

namespace KOK_Graphics
{

  enum TextureLoadFlags
  {
    TEX_DEFAULT       = 0x00,

    TEX_DETAIL_HIGH   = 0x01,
    TEX_DETAIL_MED    = 0x02,
    TEX_DETAIL_LOW    = 0x04,

    TEX_GAMMA_CORRECT = 0x08,
    TEX_COMPRESS      = 0x10,
    TEX_4BITLOAD      = 0x20

  };

  inline TextureLoadFlags operator|(TextureLoadFlags a, TextureLoadFlags b)
  {return static_cast<TextureLoadFlags>(static_cast<int>(a) | static_cast<int>(b));};

  GLuint LoadPNG(string path, TextureLoadFlags detail, bool &success);

  void LoadCubeMap(string path, string sidesNames[6], GLuint lod, GLuint cubeMap, bool usesMips);
  void LoadEnvironment(string path, GLuint& sky, GLuint& irradiance, GLuint& radiance);

  GLuint BlankPNG(GLuint width, GLuint height);
  GLuint BlankPNG16(GLuint width, GLuint height);
}

#endif

#include "KOK_Imager.h"

#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstring>

//headers for stb_image
#define STBI_ONLY_PNG
#define STBI_ONLY_TGA
#define STB_IMAGE_IMPLEMENTAION
#include "stb_image.h"
#include <stdio.h>
#include <iostream>

namespace KOK_Imager
{
	void LoadCubeMap(string path, string sidesNames[6], GLuint lod, GLuint cubeMap, bool usesMips)
	{
		//GLuint cubeMap;
		//glGenTextures(1, &cubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

		//set parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if(usesMips)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 5);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);

		int width, height, nrChannels;

		const int pSize = path.length();
		const int sSize = pSize + 32;
		char result[sSize];
		strcpy(result, path.c_str());

		//load faces

		for(GLuint i = 0; i < 6; i++)
		{
			unsigned char * data;

			memset(&result[pSize], 0, 32); //reset path end
			strcat(result, sidesNames[i].c_str());
			data = stbi_load(result, &width, &height, &nrChannels, 0);

			if(data)
			{
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					lod, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);

				stbi_image_free(data);
			}
			else
			{
				cout << "CUBE MAP LOAD ERROR " << sidesNames[i] << endl;
				stbi_image_free(data);
			}
		}

		cout << "loaded cubemap success!!!" << endl;
	}



	void LoadEnvironment(string path, GLuint& sky, GLuint& irradiance, GLuint& radiance)
	{
		string sidesNames[6] =//array to hold names of sides to load
		{
				"sky_posx.tga",
				"sky_negx.tga",
				"sky_posy.tga",
				"sky_negy.tga",
				"sky_posz.tga",
				"sky_negz.tga"
		};

		//skybox first
		glGenTextures(1, &sky);
		LoadCubeMap(path, sidesNames, 0, sky, false);

		//irradiance
		sidesNames[0] = "irradiance_posx.tga";
		sidesNames[1] = "irradiance_negx.tga";
		sidesNames[2] = "irradiance_posy.tga";
		sidesNames[3] = "irradiance_negy.tga";
		sidesNames[4] = "irradiance_posz.tga";
		sidesNames[5] = "irradiance_negz.tga";

		glGenTextures(1, &irradiance);
		LoadCubeMap(path, sidesNames, 0, irradiance, false);

		//radiance lod 0
		sidesNames[0] = "radiance_posx_0_256x256.tga";
		sidesNames[1] = "radiance_negx_0_256x256.tga";
		sidesNames[2] = "radiance_posy_0_256x256.tga";
		sidesNames[3] = "radiance_negy_0_256x256.tga";
		sidesNames[4] = "radiance_posz_0_256x256.tga";
		sidesNames[5] = "radiance_negz_0_256x256.tga";

		glGenTextures(1, &radiance);
		LoadCubeMap(path, sidesNames, 0, radiance, true);

		//radiance lod 1
		sidesNames[0] = "radiance_posx_1_128x128.tga";
		sidesNames[1] = "radiance_negx_1_128x128.tga";
		sidesNames[2] = "radiance_posy_1_128x128.tga";
		sidesNames[3] = "radiance_negy_1_128x128.tga";
		sidesNames[4] = "radiance_posz_1_128x128.tga";
		sidesNames[5] = "radiance_negz_1_128x128.tga";

		LoadCubeMap(path, sidesNames, 1, radiance, true);

		//radiance lod 2
		sidesNames[0] = "radiance_posx_2_64x64.tga";
		sidesNames[1] = "radiance_negx_2_64x64.tga";
		sidesNames[2] = "radiance_posy_2_64x64.tga";
		sidesNames[3] = "radiance_negy_2_64x64.tga";
		sidesNames[4] = "radiance_posz_2_64x64.tga";
		sidesNames[5] = "radiance_negz_2_64x64.tga";

		LoadCubeMap(path, sidesNames, 2, radiance, true);

		//radiance lod 3
		sidesNames[0] = "radiance_posx_3_32x32.tga";
		sidesNames[1] = "radiance_negx_3_32x32.tga";
		sidesNames[2] = "radiance_posy_3_32x32.tga";
		sidesNames[3] = "radiance_negy_3_32x32.tga";
		sidesNames[4] = "radiance_posz_3_32x32.tga";
		sidesNames[5] = "radiance_negz_3_32x32.tga";

		LoadCubeMap(path, sidesNames, 3, radiance, true);

		//radiance lod 4
		sidesNames[0] = "radiance_posx_4_16x16.tga";
		sidesNames[1] = "radiance_negx_4_16x16.tga";
		sidesNames[2] = "radiance_posy_4_16x16.tga";
		sidesNames[3] = "radiance_negy_4_16x16.tga";
		sidesNames[4] = "radiance_posz_4_16x16.tga";
		sidesNames[5] = "radiance_negz_4_16x16.tga";

		LoadCubeMap(path, sidesNames, 4, radiance, true);

		//radiance lod 5
		sidesNames[0] = "radiance_posx_5_8x8.tga";
		sidesNames[1] = "radiance_negx_5_8x8.tga";
		sidesNames[2] = "radiance_posy_5_8x8.tga";
		sidesNames[3] = "radiance_negy_5_8x8.tga";
		sidesNames[4] = "radiance_posz_5_8x8.tga";
		sidesNames[5] = "radiance_negz_5_8x8.tga";

		LoadCubeMap(path, sidesNames, 5, radiance, true);

	}

	GLuint LoadPNG(string path, bool gamma, bool compress, bool &success)
	{
		cout << "LOADING TEXTURE : " + path << endl;

		//load defaults
		//DefaultTexture defaultTex = DefaultTexture();

		GLuint tex_2d;
		glGenTextures(1, &tex_2d);
		glBindTexture(GL_TEXTURE_2D, tex_2d);
		int width, height, nrChannels;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data)
		{
			GLenum internalFormat = GL_RGBA8;

			if(gamma) internalFormat = GL_SRGB8_ALPHA8;
			if(compress) internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM;
			if(compress && gamma) internalFormat = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;

			glTexStorage2D(GL_TEXTURE_2D, 3, internalFormat, width, height);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);
			cout << "LOADED: " << tex_2d << endl;
			success = true;
		}
		else
		{
			cout << "FUCKING IMAGE LOAD ERROR" << endl;
			success = false;
			//stbi_image_free(data);
			//return defaultTex.texture;
		}

		stbi_image_free(data);

		return tex_2d;
	}

	GLuint BlankPNG(GLuint width, GLuint height)
	{
		GLuint tex_2d;
		glGenTextures(1, &tex_2d);
		glBindTexture(GL_TEXTURE_2D, tex_2d);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		return tex_2d;
	}

	GLuint BlankPNG16(GLuint width, GLuint height)
	{
		GLuint tex_2d;
		glGenTextures(1, &tex_2d);
		glBindTexture(GL_TEXTURE_2D, tex_2d);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

		return tex_2d;
	}

}

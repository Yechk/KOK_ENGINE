#include "KOK_Imager.h"

#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstring>

//headers for stb_image
#define STB_IMAGE_IMPLEMENTAION
#include "stb_image.h"
#include <stdio.h>
#include <iostream>

namespace KOK_Imager
{
	GLuint LoadCubeMap(string path)
	{
		GLuint cubeMap;
		glGenTextures(1, &cubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

		//set parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

		int width, height, nrChannels;

		const int pSize = path.length();
		const int sSize = pSize + 9;
		char result[sSize];
		strcpy(result, path.c_str());

		//sides names
		string sidesNames[6] = {
			"right.png",
			"left.png",
			"up.png",
			"down.png",
			"back.png",
			"front.png"
		};

		string dirNames[6] = {
			"px.png",
			"nx.png",
			"py.png",
			"ny.png",
			"pz.png",
			"nz.png"
		};

		//load faces

		for(GLuint i = 0; i < 6; i++)
		{
			unsigned char * data;

			memset(&result[pSize], 0, 9); //reset path end
			strcat(result, sidesNames[i].c_str());
			data = stbi_load(result, &width, &height, &nrChannels, 0);

			if(!data) //try another convention
			{
				memset(&result[pSize], 0, 9); //reset path end
				strcat(result, dirNames[i].c_str());
				data = stbi_load(result, &width, &height, &nrChannels, 0);
			}

			if(data)
			{
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
				);

				stbi_image_free(data);
			}
			else
			{
				cout << "CUBE MAP LOAD ERROR " << sidesNames[i] << endl;
				stbi_image_free(data);
			}
		}

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		cout << "loaded cubemap success!!!" << endl;
		return cubeMap;
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

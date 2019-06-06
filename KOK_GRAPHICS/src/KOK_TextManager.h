//text manager
#ifndef KOK_TEXTMANAGER_H
#define KOK_TEXTMANAGER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "KOK_Imager.h"
#include <map>

using namespace std;

namespace KOK_Graphics
{

	class KOK_TextManager
	{
	public:
		FT_Library library;
		FT_Face face;

		glm::mat4 projection;

		GLuint VAO;
		GLuint VBO;

		struct square
		{
			GLuint VAO;
			GLuint VBO;
			GLuint EBO;

			GLuint shader;
			GLuint imageShader;
		};

		struct EffectShaders
		{
			GLuint threshold;
			GLuint blur;
			GLuint blurH;
			GLuint blurV;
			GLuint additive;
			GLuint copy;

			//image buffers
			GLuint effectBuffer0;
			GLuint effectBuffer1;

			EffectShaders()
			{
				threshold = LoadComputeShader("./Shaders/ImageProcess/brightThreshold.glsl");
				blur = LoadComputeShader("./Shaders/ImageProcess/imageBlur.glsl");
				blurH = LoadComputeShader("./Shaders/ImageProcess/imageBlurH.glsl");
				blurV = LoadComputeShader("./Shaders/ImageProcess/imageBlurV.glsl");
				additive = LoadComputeShader("./Shaders/ImageProcess/imageAdditive.glsl");
				copy = LoadComputeShader("./Shaders/ImageProcess/copyCompute.glsl");

				GLuint effectBuffer0 = BlankPNG(1280, 720);
				GLuint effectBuffer1 = BlankPNG(1280, 720);
			};

			GLuint Bloom(GLuint bloomMap)
			{

				glUseProgram(copy);
				glBindImageTexture(0, bloomMap, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
				glBindImageTexture(1, effectBuffer0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
				glDispatchCompute(80, 45, 1);

				//glUseProgram(blurH);
				//glBindImageTexture(3, effectBuffer0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
				//glBindImageTexture(4, effectBuffer1, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
				//glDispatchCompute(80, 45, 1);

				//glUseProgram(blurV);
				//glBindImageTexture(3, effectBuffer1, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
				//glBindImageTexture(5, bloomMap, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
				//glDispatchCompute(80, 45, 1);

				return effectBuffer0;
			}
		};

		EffectShaders * effects;

		GLuint shader;

		square sq;

		KOK_TextManager(const char * file, const GLint& width, const GLint& height);
		~KOK_TextManager();

		void DrawText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		void DrawBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height, glm::vec3 color);

		void DrawSplash(GLfloat width, GLfloat height, GLuint baseImage, GLuint buffer0, GLuint buffer1, glm::vec4 cm=glm::vec4(1.0f));
		void DrawSprite(GLfloat width, GLfloat height, GLfloat posX, GLfloat posY, GLuint texture, glm::vec4 cm=glm::vec4(1.0f));

		//draws a box with text
		void DrawTextBox(const std::string& text, const GLfloat& x, const GLfloat& y, const GLfloat& width,
			const GLfloat& height, const GLfloat& fontSize, const glm::vec3& textColor, const glm::vec3& boxColor);


		struct Character
		{
			GLuint TextureID;
			glm::ivec2 Size;
			glm::ivec2 Bearing;
			GLuint Advance;
		};

		std::map<GLchar, Character> Characters;
	};

}

#endif

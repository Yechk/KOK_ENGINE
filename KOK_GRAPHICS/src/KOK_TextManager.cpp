//text manager
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include "KOK_TextManager.h"
#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace KOK_Graphics
{

	KOK_TextManager::KOK_TextManager(const char * file, const GLint& width, const GLint& height)
	{
		if (FT_Init_FreeType(&library))
			cout << "error init FreeType" << endl;
		if (FT_New_Face(library, file, 0, &face))
			cout << "failed to load font" << file << endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				cout << "Failed to load glyph" << endl;
				continue;
			}

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			//set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x
			};

			Characters.insert(pair<GLchar, Character>(c, character));

		}
			glBindTexture(GL_TEXTURE_2D, 0);


			FT_Done_Face(face);
			FT_Done_FreeType(library);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			shader = LoadShaders("./Shaders/text.vs","./Shaders/text.fs");


			//set up text box
			GLfloat w = 100.0f;
			GLfloat h = 100.0f;
			GLfloat px = 100.0f;
			GLfloat py = 100.0f;

			GLfloat vertices[16] = {0.0f, 0.0f,
															0.0f, 0.0f,
															0.0f, 0.0f,
															0.0f, 0.0f,
															0.0f, 1.0f,
															1.0f, 1.0f,
															1.0f, 0.0f,
															0.0f, 0.0f};

			GLuint indices[6] = {0,1,2,0,2,3};

			glGenVertexArrays(1, &sq.VAO);
			glGenBuffers(1, &sq.VBO);
			glGenBuffers(1, &sq.EBO);

			glBindVertexArray(sq.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, &vertices[0], GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)32);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sq.EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glBindVertexArray(0);

			sq.shader = LoadShaders("./Shaders/hud.vs","./Shaders/hud.fs");
			sq.imageShader = LoadShaders("./Shaders/hud.vs","./Shaders/hudImage.fs");

			effects = new EffectShaders();
	}

	void KOK_TextManager::DrawTextBox(const std::string& text, const GLfloat& x, const GLfloat& y,
			const GLfloat& width, const GLfloat& height, const GLfloat& fontSize, const glm::vec3& textColor, const glm::vec3& boxColor)
	{
		DrawBox(x, y, width, height, boxColor);
		DrawText(text, x - width + 8, y + width - 24, fontSize, textColor);

	}

	void KOK_TextManager::DrawBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height, glm::vec3 color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	  // Activate corresponding render state
	  glUseProgram(sq.shader);

		SetUniformVec2(sq.shader, "origin", x, y);
		SetUniformVec2(sq.shader, "dims", width, height);

	  glUniform3f(glGetUniformLocation(sq.shader, "textColor"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(sq.shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	  glBindVertexArray(sq.VAO);

		GLfloat vertices[] = {
			x, y,
			x - width, y,
			x - width, y + height,
			x, y + height
		};

	  glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);
	  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	  glBindVertexArray(0);
	}

	void KOK_TextManager::DrawSprite(GLfloat width, GLfloat height, GLfloat posX, GLfloat posY, GLuint texture, glm::vec4 cm)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(sq.imageShader);

		SetUniformTexture(sq.imageShader,"imaget", 0);
		SetUniformVec4(sq.imageShader, "colorMod", cm.x, cm.y, cm.z, cm.w);
		glUniformMatrix4fv(glGetUniformLocation(sq.imageShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(sq.VAO);

		GLfloat y = posY;
		GLfloat x = posX;

		GLfloat vertices[] = {
			x, y,
			x + width, y,
			x + width, y + height,
			x, y + height,
		};

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void KOK_TextManager::DrawSplash(GLfloat width, GLfloat height, GLuint baseImage, GLuint buffer0, GLuint buffer1, glm::vec4 cm)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLfloat x = 0.0f;
		GLfloat y = 0.0f;

		//GLint val = 0;
		//glGetIntegeri_v(GL_IMAGE_BINDING_LEVEL, baseImage, &val);
		//cout << "binding level: " << val << endl;

		glUseProgram(effects->threshold);
		glBindImageTexture(0, baseImage, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindImageTexture(1, buffer0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glDispatchCompute(80, 45, 1);

		glUseProgram(effects->blurH);
		glBindImageTexture(0, buffer0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindImageTexture(1, buffer1, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glDispatchCompute(80, 45, 1);

		glUseProgram(effects->blurV);
		glBindImageTexture(0, buffer1, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindImageTexture(1, buffer0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glDispatchCompute(80, 45, 1);

		glUseProgram(effects->additive);
		glBindImageTexture(0, baseImage, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindImageTexture(1, buffer0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		glBindImageTexture(2, buffer1, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
		glDispatchCompute(80, 45, 1);

		//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	  //  Render the final splash image
	  glUseProgram(sq.imageShader);

		SetUniformTexture(sq.imageShader,"imaget", 0);
		SetUniformVec4(sq.imageShader, "colorMod", cm.x, cm.y, cm.z, cm.w);
		glUniformMatrix4fv(glGetUniformLocation(sq.imageShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	  glBindVertexArray(sq.VAO);

		GLfloat vertices[] = {
			x, y,
			x + width, y,
			x + width, y + height,
			x, y + height
		};

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, buffer1);

	  glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);
	  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	  glBindVertexArray(0);
	}


	void KOK_TextManager::DrawText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
	{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    // Activate corresponding render state
	  glUseProgram(shader);
	  glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	  glActiveTexture(GL_TEXTURE0);
	  glBindVertexArray(VAO);

	  // Iterate through all characters
	  std::string::const_iterator c;

		GLfloat origX = x;

	  for (c = text.begin(); c != text.end(); c++)
	  {
		  Character ch = Characters[*c];

			if (*c == '\n')
			{
				y -= (ch.Size.y * scale) + 8;
				x = origX;
				continue;
			}

		  GLfloat xpos = x + ch.Bearing.x * scale;
		  GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		  GLfloat w = ch.Size.x * scale;
		  GLfloat h = ch.Size.y * scale;
		  // Update VBO for each character
		  GLfloat vertices[6][4] = {
		      { xpos,     ypos + h,   0.0, 0.0 },
		      { xpos,     ypos,       0.0, 1.0 },
		      { xpos + w, ypos,       1.0, 1.0 },

		      { xpos,     ypos + h,   0.0, 0.0 },
		      { xpos + w, ypos,       1.0, 1.0 },
		      { xpos + w, ypos + h,   1.0, 0.0 }
		  };
		  // Render glyph texture over quad
		  glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		  // Update content of VBO memory
		  glBindBuffer(GL_ARRAY_BUFFER, VBO);
		  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		  glBindBuffer(GL_ARRAY_BUFFER, 0);
		  // Render quad
		  glDrawArrays(GL_TRIANGLES, 0, 6);
		  // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		  x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	  }
	  glBindVertexArray(0);
	  glBindTexture(GL_TEXTURE_2D, 0);
	}

}

#ifndef KOK_TEXTCONSOLE_H
#define KOK_TEXTCONSOLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "KOK_TextManager.h"
#include <map>
#include <string>
#include <functional>

using namespace std;


namespace KOK_Graphics
{

	class KOK_TextConsole
	{
	private:
		GLuint _maxLines;
		GLuint _lineWidth;

		struct lineInfo
		{
			std::string line;
			glm::vec3 color;
		};

		std::vector<lineInfo> _lines;
		std::string _commandBuffer;

		map<std::string,std::function<void()>> commands;


	public:
		void Print(std::string text, glm::vec3 color);
		void Clear();

		void Draw(KOK_TextManager * textManager, GLfloat posX, GLfloat posY, glm::vec3 color);
		void AddCharacter(GLint codepoint);

		void AddCommand(string name,
			std::function<void()> command);

		void DeleteCharacter();
		void ClearInput();
		void Return();

		bool ExecuteCommand(std::string input);

		KOK_TextConsole(GLuint lineWidth, GLuint maxLines);
		~KOK_TextConsole();

	};

}

#endif

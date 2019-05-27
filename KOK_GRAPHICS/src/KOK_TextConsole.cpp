

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <functional>
#include <string>

#include "KOK_TextConsole.h"
#include "KOK_TextManager.h"

using namespace std;

KOK_TextConsole::KOK_TextConsole(GLuint lineWidth, GLuint maxLines)
{
	_lineWidth = lineWidth * 8;
	_maxLines = maxLines;
}

void KOK_TextConsole::Print(std::string text, glm::vec3 color)
{
	_lines.push_back(lineInfo());
	_lines.back().line = text;
	_lines.back().color = color;
}

void KOK_TextConsole::Draw(KOK_TextManager * textManager, GLfloat posX, GLfloat posY, glm::vec3 color)
{
	int lineSpace = 24;

	//main box
	textManager->DrawBox(posX, posY, _lineWidth, _maxLines * lineSpace, color);

	int offset = 0;

	//text lines
	for(int i = 0; i < _lines.size(); i++)
	{
		textManager->DrawText(_lines[i].line, posX - _lineWidth + 8, posY + (_maxLines * lineSpace) - offset - lineSpace + 4,
			 0.35f, _lines[i].color);
		offset += lineSpace;
	}

	////input box
	textManager->DrawBox(posX, posY, _lineWidth, lineSpace, color);
	textManager->DrawText("> " + _commandBuffer, posX - _lineWidth + 8, posY + 5, 0.35f, glm::vec3(1.0f));
}

void KOK_TextConsole::AddCharacter(GLint codepoint)
{
	_commandBuffer += codepoint;
}

void KOK_TextConsole::DeleteCharacter()
{
	_commandBuffer = _commandBuffer.substr(0, _commandBuffer.size()-1);
}

void KOK_TextConsole::ClearInput()
{
	_commandBuffer = "";
}

void KOK_TextConsole::Return()
{
	//if(!ExecuteCommand(_commandBuffer)) Print("Command Not Found: " + _commandBuffer, glm::vec3(1.0f,0.3f,0.3f));
	ClearInput();
}

void KOK_TextConsole::AddCommand(string name,
	std::function<void()> command)
{
	if(commands.find(name) != commands.end()) return;

	commands[name] = command;
}

bool KOK_TextConsole::ExecuteCommand(std::string input)
{
	if(commands.find(input) == commands.end()) return false;

	commands[input]();

	return true;
}

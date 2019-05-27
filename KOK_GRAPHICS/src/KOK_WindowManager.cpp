#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "KOK_WindowManager.h"
//

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include "Camera.h"

using namespace std;
#include "KOK_TextConsole.h"
#include "KOK_TextManager.h"
#include "KOK_Message.h"
#include "KOK_Imager.h"

#include <memory>

//KOK Window manager cpp
void KOK_WindowManager::InitGUI(GLFWwindow* window, GLint width, GLint height)
{
	glfwSetCursorPosCallback(window, &KOK_WindowManager::GUICursorCallback);
	glfwSetMouseButtonCallback(window, &KOK_WindowManager::GUIMouseButtonCallback);
	glfwSetDropCallback(window, &KOK_WindowManager::GUIDropCallback);
	glfwSetScrollCallback(window, &KOK_WindowManager::GUIScrollCallback);
	glfwSetFramebufferSizeCallback(window, &KOK_WindowManager::GUIFrameSizeCallback);
	glfwSetKeyCallback(window, &KOK_WindowManager::GUIKeyCallback);
	glfwSetCharCallback(window, &KOK_WindowManager::GUICharCallback);

	_textManager = new KOK_TextManager("Fonts/Menlo-Regular.ttf", width, height);
}

void KOK_WindowManager::DrawGUI()
{
	for(int i = 0; i < _windows.size(); i++)
	{
		_windows[i]->Draw(_textManager);
	}
}

void KOK_WindowManager::UpdateGUI()
{
	office->Update(INTERLEAVE);

	for(int i = 0; i < _windows.size(); i++)
	{
		_windows[i]->Update(0.0);
	}
}

KOK_WindowManager::KOK_WindowManager()
{
	office = new KOK_PostOffice(64);
}

KOK_WindowManager::~KOK_WindowManager()
{

}

void KOK_WindowManager::GUICursorCallback(GLFWwindow * window, double x, double y)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	MouseData::mouseX = x;
	MouseData::mouseY = (double)height - y;
}

void KOK_WindowManager::GUIMouseButtonCallback(GLFWwindow * window, int button, int action, int modifiers)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(action == GLFW_PRESS) MouseData::leftPressed = true;
		else MouseData::leftPressed = false;
	}

	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS) MouseData::rightPressed = true;
		else MouseData::rightPressed = false;
	}
}

void KOK_WindowManager::GUIDropCallback(GLFWwindow * window, int count, const char **filenames)
{

}

void KOK_WindowManager::GUIKeyCallback(GLFWwindow * w, int key, int scancode, int action, int mods)
{


	// If a key is pressed, toggle the relevant key-press flag
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_BACKSPACE:
			//console->DeleteCharacter();
			break;
		case GLFW_KEY_ENTER:
			//console->Return();
			break;
		case GLFW_KEY_TAB:

			break;
		case GLFW_KEY_W:

			break;
		case GLFW_KEY_S:

			break;
		case GLFW_KEY_A:

			break;
		case GLFW_KEY_D:

			break;
		default:
			// Do nothing...
			break;
		}
	}

	if(action == GLFW_RELEASE) // If a key is released, toggle the relevant key-release flag
	{
		switch (key)
		{
		case GLFW_KEY_TAB:

			break;
		case GLFW_KEY_W:

			break;
		case GLFW_KEY_S:

			break;
		case GLFW_KEY_A:

			break;
		case GLFW_KEY_D:

			break;
		default:
			// Do nothing...
			break;
		}
	}
}

void KOK_WindowManager::GUICharCallback(GLFWwindow *w, unsigned int codepoint)
{

}

void KOK_WindowManager::GUIScrollCallback(GLFWwindow * window, double x, double y)
{

}

void KOK_WindowManager::GUIFrameSizeCallback(GLFWwindow * window, int width, int height)
{

}

void KOK_WindowManager::CreateWindow(GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool fixed, string label)
{
	_windows.push_back(new KOK_WM_Window(x, y, width, height, fixed, label, office));
}

KOK_WM_Widget *  KOK_WindowManager::AddWidget(string window, string widget, WidgetType type, GLfloat offsetX, GLfloat offsetY, bool grid)
{
	string sized = window;
	sized.resize(32, ' ');

	for(int i = 0; i < _windows.size(); i++)
	{
		if(_windows[i]->label == sized)
		{
				return _windows[i]->AddWidget(type, widget, offsetX, offsetY, grid);
		}
	}
	cout << "Window not found when adding widget." << endl;
	return NULL;
}


///window functions
void KOK_WM_Window::Draw()
{
}

void KOK_WM_Window::Draw(KOK_TextManager * manager)
{
	manager->DrawBox(x, y, width, height, colorMain);
	manager->DrawBox(x - (width - 32.0f), y, 32.0f, height, colorDark);
	manager->DrawBox(x, y + (height-32.0f), width, 32.0f, colorLight);

	manager->DrawText(label, x - width + 4, y + height - 24.0f, 0.5f, colorDark);

	for(int i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->Draw(manager);
	}
}

void KOK_WM_Window::DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender)
{
	//prints message data

	//TODO: not fixed && check if mouse is clicked && in range
	//MouseData * mData = static_cast<MouseData*>(data.p);
}

void KOK_WM_Window::Update(double time)
{
	for(int i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->Update(0.0);
	}
}

KOK_WM_Widget * KOK_WM_Window::AddWidget(WidgetType w, string l, GLfloat offsetX, GLfloat offsetY, bool grid)
{
	KOK_WM_Widget * wid = NULL;

	if(w == LABEL)
	{
		wid = new KOK_WM_Widget_Label(l);
	}

	if(w == SLIDER)
	{
		wid = new KOK_WM_Widget_Slider(l);
	}

	wid->SetOffset((offsetX * xGridOffset) - width + 38.0f, (-offsetY * yGridOffset) + height - 68.0f);
	wid->SetParent(this);
	_widgets.push_back(wid);
	return wid;
}

//widget class

void KOK_WM_Widget::Draw()
{

}

void KOK_WM_Widget::Draw(KOK_TextManager * manager)
{

}

void KOK_WM_Widget::DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender)
{
	if(subject == 2) //change label to string
	{
		memcpy(&label, data.p, 32);
	}
}

void KOK_WM_Widget::Update(double time)
{

}

void KOK_WM_Widget::CalcOffset(GLfloat &posX, GLfloat &posY)
{
	posX = offsetX;
	posY = offsetY;

	if(_parent != NULL)
	{
		posX += _parent->x;
		posY += _parent->y;
	}
};

//label widget class

void KOK_WM_Widget_Label::Draw()
{

}

void KOK_WM_Widget_Label::Draw(KOK_TextManager * manager)
{
	GLfloat posX;
	GLfloat posY;

	CalcOffset(posX, posY);

	manager->DrawText(label, posX, posY, 0.5f, _parent->colorLight);
}

void KOK_WM_Widget_Label::DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender)
{
	if(subject == 3) //change label to double
	{
		label = to_string(data.d);//
	}

	if(subject == 10) //change label to uint
	{
		label = to_string(data.ui);//
	}

}

void KOK_WM_Widget_Label::Update(double time)
{

}

//slider widget class

void KOK_WM_Widget_Slider::Draw(KOK_TextManager * manager)
{
	GLfloat posX;
	GLfloat posY;

	CalcOffset(posX, posY);

	uint dotOffset = (uint)_value;

	manager->DrawBox(posX+SLIDER_BAR_OFFSET_X, posY+SLIDER_BAR_OFFSET_Y, 100.0f, 8.0f, _parent->colorDark);
	manager->DrawSprite(16.0f, 16.0f, posX+SLIDER_DOT_OFFSET_X+dotOffset, posY+SLIDER_DOT_OFFSET_Y,
		KOK_WindowManager::Textures::circle16, glm::vec4(_parent->colorLight, 1.0f));
}

void KOK_WM_Widget_Slider::DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender)
{
	if(subject == 3) //change value from uint
	{
		_value = (double)data.ui;//
	}

	if(subject == 4) //change value from float
	{
		_value = (double)(data.f * 255);//
	}

	if(subject == 5) //return value
	{
		_parent->office->QueueMessage(10, (uint)_value, sender, this, MEDIA);
	}
}

void KOK_WM_Widget_Slider::Update(double time)
{
	GLfloat posX;
	GLfloat posY;

	CalcOffset(posX, posY);

	double lowerX = (double)(posX);
	double lowerY = (double)(posY+SLIDER_BAR_OFFSET_Y - 4.0f);

	double upperX = lowerX + (double)SLIDER_RANGE_X + 6.0;
	double upperY = lowerY + (double)SLIDER_RANGE_Y;

	double mouseX = KOK_WindowManager::MouseData::mouseX;
	double mouseY = KOK_WindowManager::MouseData::mouseY;

	if(moving || (mouseX > lowerX && mouseX < upperX && mouseY > lowerY && mouseY < upperY))
	{
		if(KOK_WindowManager::MouseData::leftPressed)
		{
			_value = min(mouseX - lowerX, 100.0);
			if(_value < 0.0) _value = 0.0;
			moving = true;
		}
	}

	if(!KOK_WindowManager::MouseData::leftPressed)
	{
		moving = false;
	}
}

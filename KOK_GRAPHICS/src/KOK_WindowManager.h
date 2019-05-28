#ifndef KOK_WINDOWMANAGER_H
#define KOK_WINDOWMANAGER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include "KOK_TextConsole.h"
#include "KOK_TextManager.h"
#include "KOK_Message.h"

#include "KOK_Imager.h"

using namespace std;

//slider widget macros
#define SLIDER_DOT_OFFSET_X -6.0f
#define SLIDER_DOT_OFFSET_Y 6.0f
#define	SLIDER_BAR_OFFSET_X 104.0f
#define	SLIDER_BAR_OFFSET_Y 10.0f
#define SLIDER_RANGE_X 100.0f
#define SLIDER_RANGE_Y 16.0f

enum WidgetType
{
	BLANK,
	LABEL,
	BUTTON,
	SLIDER
};

class KOK_WM_Window;

class KOK_WM_Widget : public KOK_Actor
{
protected:
	KOK_WM_Window * _parent = NULL;

	GLfloat offsetX = 0.0f;
	GLfloat offsetY = 0.0f;

public:
	WidgetType _type = BLANK;

	KOK_WM_Widget() : KOK_Actor() {};
	KOK_WM_Widget(string l) : KOK_Actor(l) {};

	void Draw();
	virtual void Draw(KOK_TextManager * manager);
	void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender);
	void Update(double time);

	inline void SetParent(KOK_WM_Window * p) {_parent = p;};
	inline void SetOffset(GLfloat x, GLfloat y) {offsetX = x; offsetY = y;};

	void CalcOffset(GLfloat &posX, GLfloat &posY);
};

class KOK_WM_Widget_Label : public KOK_WM_Widget
{
public:
	KOK_WM_Widget_Label(string l) : KOK_WM_Widget(l) {_type = LABEL;};
	void Draw();
	void Draw(KOK_TextManager * manager);
	void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender);
	void Update(double time);
};

class KOK_WM_Widget_Slider : public KOK_WM_Widget
{
private:
	double _value = 50.0;
	bool moving = false;

public:
	KOK_WM_Widget_Slider(string l) : KOK_WM_Widget(l) {_type = SLIDER;};
	void Draw() {};
	void Draw(KOK_TextManager * manager);
	void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender);
	void Update(double time);
};

class KOK_WM_Window : public KOK_Actor
{
	//TODO::Grid spacing. divide by width and height of window. adding a widget can specift a grid location.

private:

	friend class KOK_WM_Widget;
	friend class KOK_WM_Widget_Label;
	friend class KOK_WM_Widget_Slider;

	KOK_PostOffice * office;

	GLfloat width;
	GLfloat height;

	GLfloat x;
	GLfloat y;

	GLfloat xGridOffset;
	GLfloat yGridOffset;

	bool fixed;

	//TODO: add changable color schemes

	//glm::vec3 colorMain = glm::vec3(0.804f, 0.722f, 0.329f); some kind of orange
	//glm::vec3 colorLight = glm::vec3(0.961f, 0.890f, 0.545f);
	//glm::vec3 colorDark = glm::vec3(0.667f, 0.584f, 0.188f);

	//glm::vec3 colorMain = glm::vec3(0.424f, 0.2f, 0.29f); gay purple
	//glm::vec3 colorLight = glm::vec3(0.596f, 0.318f, 0.506f);
	//glm::vec3 colorDark = glm::vec3(0.314f, 0.0f, 0.212f);

	glm::vec3 colorMain = glm::vec3(0.157f, 0.172f, 0.204f);
	glm::vec3 colorLight = glm::vec3(0.615f, 0.647f, 0.706f);
	glm::vec3 colorDark = glm::vec3(0.129f, 0.145f, 0.168f);

	inline void SetGrid()
	{
		xGridOffset = (width - 38.0f) / 3.0f;
		yGridOffset = 36.0f;
		cout << "this grid offset: " << yGridOffset << endl;
	};

public:

	//widget group
	vector<KOK_WM_Widget*> _widgets;

	KOK_WM_Window(string l) : width{64.0f}, height{64.0f}, x{0.0f}, y{0.0f}, fixed{false} {label = l; label.resize(32, ' ');};

	KOK_WM_Window(GLfloat _x, GLfloat _y, GLfloat _width, GLfloat _height, bool _fixed, string _label, KOK_PostOffice * _office) :
		x{_x}, y{_y}, width{_width}, height{_height}, fixed{_fixed}, office{_office}
	{
		label = _label;
		label.resize(32, ' ');

		SetGrid();
	};

	void Draw();
	void Draw(KOK_TextManager * manager);
	void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender);
	void Update(double time);

	KOK_WM_Widget * AddWidget(WidgetType w, string l, GLfloat offsetX, GLfloat offsetY, bool grid);
};

class KOK_WindowManager
{
private:
	KOK_TextManager * _textManager;
	vector<KOK_WM_Window*> _windows;

	//callbacks for windows
	static void GUICursorCallback(GLFWwindow * window, double x, double y);
	static void GUIMouseButtonCallback(GLFWwindow * window, int button, int action, int modifiers);
	static void GUIDropCallback(GLFWwindow * window, int count, const char **filenames);
	static void GUIScrollCallback(GLFWwindow * window, double x, double y);
	static void GUIFrameSizeCallback(GLFWwindow * window, int width, int height);
	static void GUIKeyCallback(GLFWwindow * w, int key, int scancode, int action, int mods);
	static void GUICharCallback(GLFWwindow *w, unsigned int codepoint);

public:
	KOK_PostOffice * office;

	struct MouseData
	{
	  static double mouseX;
		static double mouseY;
		static bool leftPressed;
		static bool rightPressed;
	};

	struct Textures
	{
		static GLuint circle16;
	};

	void InitGUI(GLFWwindow* window, GLint width, GLint height);
	void UpdateGUI();
	void DrawGUI();
	void CreateWindow(GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool fixed, string label);

  KOK_WM_Widget * AddWidget(string window, string widget, WidgetType type, GLfloat offsetX, GLfloat offsetY, bool grid);

	KOK_WindowManager();
	~KOK_WindowManager();
};

double KOK_WindowManager::MouseData::mouseX = 0.0;
double KOK_WindowManager::MouseData::mouseY = 0.0;
bool KOK_WindowManager::MouseData::leftPressed = false;
bool KOK_WindowManager::MouseData::rightPressed = false;
GLuint KOK_WindowManager::Textures::circle16 = 0;

inline void InitWindowTextures()
{
	bool success;
	KOK_WindowManager::Textures::circle16 = KOK_Imager::LoadPNG("./Textures/UI/circle16.png", false, success);
};

#endif

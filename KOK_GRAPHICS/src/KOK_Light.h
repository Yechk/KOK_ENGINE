#ifndef KOK_LIGHT_H
#define KOK_LIGHT_H

#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class KOK_Light
{
public:
	glm::vec3 GetColor() const {return _color;};
	void SetColor(glm::vec3 color) {_color = color;};

	bool GetActive() const {return _active;};
	void SetActive(bool active) {_active = active;};

	KOK_Light(glm::vec3 color, bool active);
	~KOK_Light();

protected:
	glm::vec3 _color;
	bool _active;
};

class KOK_PointLight : public KOK_Light
{
public:

	KOK_PointLight(glm::vec3 color, bool active);
	KOK_PointLight(glm::vec3 position, float radius, GLuint power, glm::vec3 color, bool active);
	void GetPointLightInfo(bool& active, float& radius, float& power, glm::vec3& color);
	void SetPointLightInfo(bool active, float radius, float power, glm::vec3 color);

	glm::vec3 GetPosition() const {return _position;};
	void SetPosition(glm::vec3 position) {_position = position;};

private:
	float _radius;
	GLuint _power;
	glm::vec3 _position;

};

#endif

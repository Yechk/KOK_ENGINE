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
	const glm::vec3& Color() const;
	void Color(const glm::vec3& color);

	const bool Active() const;
	void Active(const bool active);

	KOK_Light(const glm::vec3& color, const bool active);
	~KOK_Light();

private:
	glm::vec3 _color;
	bool _active;
};

class KOK_PointLight : public KOK_Light
{
public:

	KOK_PointLight(const glm::vec3& color, const bool active);
	KOK_PointLight(const glm::vec3& position, const float& radius, const GLuint& power, const glm::vec3& color, const bool active);
	void GetPointLightInfo(bool& active, float& radius, float& power, glm::vec3& color);
	void SetPointLightInfo(const bool& active, const float& radius, const float& power, const glm::vec3& color);

	const glm::vec3& Position() const;
	void Position(const glm::vec3& position);

private:
	float _radius;
	GLuint _power;
	glm::vec3 _position;

};

#endif

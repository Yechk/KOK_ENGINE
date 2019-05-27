#include <string>
using namespace std;
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "KOK_Light.h"

//headers for stb_image
#include "stb_image.h"
#include <stdio.h>
#include <iostream>

KOK_Light::KOK_Light(const glm::vec3& color, const bool active)
{
	_color = color;
	_active = active;
}

const glm::vec3& KOK_Light::Color() const
{
	return _color;
}
void KOK_Light::Color(const glm::vec3& color)
{
	_color = color;
}

const bool KOK_Light::Active() const
{
	return _active;
}
void KOK_Light::Active(const bool active)
{
	_active = active;
}

KOK_PointLight::KOK_PointLight(const glm::vec3& color, const bool active) : KOK_Light(color, active)
{
	_power = 1;
	_radius = 2.0f;
}

KOK_PointLight::KOK_PointLight(const glm::vec3& position, const float& radius, const GLuint& power, const glm::vec3& color, const bool active) :
	KOK_Light(color, active)
{
	_position = position;
	_power = power;
  _radius = radius;
}

void KOK_PointLight::GetPointLightInfo(bool& active, float& radius, float& power, glm::vec3& color)
{
	active = KOK_Light::Active();
	radius = _radius;
	power = _power;
	color = KOK_Light::Color();
}

void KOK_PointLight::SetPointLightInfo(const bool& active, const float& radius, const float& power, const glm::vec3& color)
{
	KOK_Light::Active(active);
	_radius = radius;
	_power = power;
	KOK_Light::Color(color);
}

const glm::vec3& KOK_PointLight::Position() const
{
	return _position;
}

void KOK_PointLight::Position(const glm::vec3& position)
{
	_position = position;
}

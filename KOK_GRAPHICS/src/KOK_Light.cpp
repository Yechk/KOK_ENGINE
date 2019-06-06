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

KOK_Light::KOK_Light(glm::vec3 color, bool active)
{
	_color = color;
	_active = active;
}

KOK_PointLight::KOK_PointLight(glm::vec3 color, bool active) : KOK_Light(color, active)
{
	_power = 1;
	_radius = 2.0f;
}

KOK_PointLight::KOK_PointLight(glm::vec3 position, float radius, GLuint power, glm::vec3 color, bool active) :
	KOK_Light(color, active)
{
	_position = position;
	_power = power;
  _radius = radius;
}

void KOK_PointLight::GetPointLightInfo(bool& active, float& radius, float& power, glm::vec3& color)
{
	active = _active;
	radius = _radius;
	power = _power;
	color = _color;
}

void KOK_PointLight::SetPointLightInfo(bool active, float radius, float power, glm::vec3 color)
{
	_active = active;
	_radius = radius;
	_power = power;
	_color = color;
}

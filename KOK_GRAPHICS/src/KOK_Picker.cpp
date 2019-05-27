//picker cpp
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string.h>
#include "KOK_Picker.h"
using namespace std;

void KOK_Picker::CalculateRay(int screenWidth, int screenHeight, float mouseX, float mouseY, glm::mat4 projection, glm::mat4 view)
{
	ndMouseX = (2.0f * mouseX) / screenWidth - 1.0f;
	ndMouseY = 1.0f - (2.0f * mouseY) / screenHeight;
	ndMouseZ = 1.0f;

	rayNDs = glm::vec3(ndMouseX, ndMouseY, ndMouseZ);

	rayClip = glm::vec4(rayNDs.x, rayNDs.y, -1.0f, 1.0f);
	rayEye = glm::inverse(projection) * rayClip;
	rayEye = glm::inverse(view) * glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

	rayWorld = glm::vec3(rayEye.x, rayEye.y, rayEye.z);
	rayWorld = glm::normalize(rayWorld);

	
}

bool KOK_Picker::CalculateSphereIntersect(glm::vec3 point, glm::vec3 sphereCenter, float radius)
{
	glm::vec3 m = point - sphereCenter;
	float b = glm::dot(m, rayWorld);
	float c = glm::dot(m, m) - (radius * radius);

	if (c > 0.0f && b > 0.0f) return false;
	
	float discr = b*b - c;
	if (discr < 0.0f) return false;

	return true;
}

glm::vec3 KOK_Picker::GetRay()
{
	return rayWorld;
}

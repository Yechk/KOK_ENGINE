#ifndef KOK_PICKER_H
#define KOK_PICKER_H

#include <glm/glm.hpp>
#include <string.h>
using namespace std;

class KOK_Picker
{
private:
	float ndMouseX;	
	float ndMouseY;
	float ndMouseZ;

	glm::vec3 rayNDs;
	glm::vec4 rayClip;
	glm::vec4 rayEye;
	glm::vec3 rayWorld;
public:
	void CalculateRay(int screenWidth, int screenHeight, float mouseX, float mouseY, glm::mat4 projection, glm::mat4 view);	
	bool CalculateSphereIntersect(glm::vec3 point, glm::vec3 sphereCenter, float radius);

	glm::vec3 GetRay(); 
};



#endif

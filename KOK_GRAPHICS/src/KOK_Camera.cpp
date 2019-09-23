#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "KOK_Camera.h"


namespace KOK_Graphics
{
	KOK_Camera::KOK_Camera()
	{
		_position = glm::vec3(0.0f);
		_target = glm::vec3(0.0f);
		_up = glm::vec3(0,1,0);
		_view = GetTargetViewMatrix();
	}
	//updates
	void KOK_Camera::Update(double time)
	{
		_view = GetTargetViewMatrix();
	}
}

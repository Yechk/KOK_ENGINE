#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "KOK_Camera.h"


namespace KOK_Graphics
{

	KOK_Camera::KOK_Camera(glm::vec3 position, glm::vec3 target)
	{
		_position = position;
		_target = target;
		_up = glm::vec3(0,1,0);
		_view = GetTargetViewMatrix();
	}

	//updates
	void KOK_Camera::Update()
	{
		_view = GetTargetViewMatrix();
	}
}

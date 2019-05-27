#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "KOK_Camera.h"

KOK_Camera::KOK_Camera(const glm::vec3& position, const glm::vec3& target)
{
	_position = position;
	_target = target;
	_up = glm::vec3(0,1,0);
	_view = GetTargetViewMatrix();
}

inline glm::mat4 KOK_Camera::GetTargetViewMatrix()
{
	return glm::lookAt(_position, _position + _target, _up);
}

//positions
const glm::vec3& KOK_Camera::Position() const
{
	return _position;
}

void KOK_Camera::Position(const glm::vec3& position)
{
	_position = position;
}

void KOK_Camera::TranslatePosition(const glm::vec3& translation)
{
	_position += translation;
}

//targets
const glm::vec3& KOK_Camera::Target() const
{
	return _target;
}

void KOK_Camera::Target(const glm::vec3& target)
{
	_target = target;
}

//view
const glm::mat4& KOK_Camera::View() const
{
	return _view;
}

//updates
void KOK_Camera::Update()
{
	_view = GetTargetViewMatrix();
}

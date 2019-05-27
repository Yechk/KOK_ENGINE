#ifndef KOK_CAMERA_H
#define KOK_CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//point camera class
class KOK_Camera
{
protected:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _up;

	glm::mat4 _view;

	inline glm::mat4 GetTargetViewMatrix();

public:
	KOK_Camera(const glm::vec3& position, const glm::vec3& target);

	void Update();

	//camera position
	const glm::vec3& Position() const;
	void Position(const glm::vec3& position);
	void TranslatePosition(const glm::vec3& translation);

	//camera target
	const glm::vec3& Target() const;
	void Target(const glm::vec3& target);
	
	//camera view
	const glm::mat4& View() const;
};


#endif

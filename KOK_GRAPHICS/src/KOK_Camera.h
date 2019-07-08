#ifndef KOK_CAMERA_H
#define KOK_CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "KOK_Actor.h"

namespace KOK_Graphics
{

	//point camera class
	class KOK_Camera : public KOK_Actor
	{
	protected:
		enum CameraFunction //different algorithms for camera control
		{
			TARGET,
			DIRECTIONAL,
			ORBIT
		} cameraFunction = ORBIT;

		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _up;

		glm::mat4 _view;

		glm::mat4 GetTargetViewMatrix()
		{
			if(cameraFunction == ORBIT)
			{
				_position = _target;

				glm::vec3 orbitPosition;
				float followDistance = 5.0f;
				orbitPosition.x = -followDistance * sin(0.0) + _position.x;
				orbitPosition.y = followDistance + _position.y;
				orbitPosition.z = -followDistance * cos(0.0) + _position.z;

				return glm::lookAt(orbitPosition, _target, _up);
			}

		  return glm::lookAt(_position, _target, _up);
		};

	public:
		KOK_Camera();
		KOK_Camera(glm::vec3 position, glm::vec3 target);

		virtual void Update(double time);
		virtual void DeliverMessage(string subject, MessageData data, KOK_Actor* sender) {};
		virtual void Draw() {};

		//camera position
		glm::vec3 GetPosition() const {return _position;};
		void SetPosition(glm::vec3 position) {_position = position;};

		void TranslatePosition(glm::vec3 translation)
		{
			_position += translation;
		};

		//camera target
		glm::vec3 GetTarget() const {return _target;};
		void SetTarget(glm::vec3 target) {_target = target;};

		//camera view
		glm::mat4 GetView() const {return _view;};
	};
}

#endif

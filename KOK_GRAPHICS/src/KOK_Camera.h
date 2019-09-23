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

		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _up;

		glm::mat4 _view;

		glm::mat4 GetTargetViewMatrix()
		{
		  return glm::lookAt(_position, _target, _up);
		};

	public:
		KOK_Camera();

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

		void SetUp(glm::vec3 up){_up = up;};

		//camera view
		glm::mat4 GetView() const {return _view;};
	};
}

#endif

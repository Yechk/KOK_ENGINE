#ifndef KOK_CAMERA_H
#define KOK_CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace KOK_Graphics
{

	//point camera class
	class KOK_Camera
	{
	protected:
		enum CameraFunction //different algorithms for camera control
		{
			TARGET,
			DIRECTIONAL
		} cameraFunction = DIRECTIONAL;

		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _up;

		glm::mat4 _view;

		glm::mat4 GetTargetViewMatrix()
		{
			if(cameraFunction == DIRECTIONAL)
		  	return glm::lookAt(_position, _position + _target, _up);

			return glm::mat4(1.0);
		};

	public:
		KOK_Camera(glm::vec3 position, glm::vec3 target);

		void Update();

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

#ifndef KOK_PHYSICSCHARACTER
#define KOK_PHYSICSCHARACTER

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "PxPhysicsAPI.h"
#include "KOK_VisualDebug.h"
#include "KOK_PhysicsContext.h"
#include "KOK_Actor.h"

using namespace std;
using namespace physx;

namespace KOK_Physics
{

  class KOK_PhysicsCharacter : public KOK_Actor
  {
  private:
    KOK_PhysicsContext * _physicsContext;
    PxController * _controller;
    double _currentTime;
    double _lastMoveTime;
    double _lastFrameTime;
    float _deltaTime;

    //need physics info for kinematic body
    glm::vec3 _velocity;
    glm::vec3 _acceleration;
    glm::vec3 _maxVelocity;
    glm::vec3 _friction;

    glm::vec3 _forwardVector;
    glm::vec3 _rightVector;
    glm::vec3 _upVector;

  public:
    KOK_PhysicsCharacter(KOK_PhysicsContext * physicsContext) : _physicsContext{physicsContext}
    {
      _velocity = glm::vec3();
      _acceleration = glm::vec3();
      _maxVelocity = glm::vec3();
      _friction = glm::vec3();

      PxCapsuleControllerDesc desc;
      desc.height = 1.0f;
      desc.radius = 0.25f;
      desc.climbingMode = PxCapsuleClimbingMode::eEASY;

      PxControllerDesc* cDesc = &desc;

      cDesc->material = physicsContext->defaultMaterial;
      cDesc->position = PxExtendedVec3(0.0f,1.0f,0.0f);

      _lastMoveTime = 0.0;
      _lastFrameTime = 0.0;

      _controller = _physicsContext->characterManager->createController(*cDesc);
    };

    void SetPosition(glm::vec3 position)
    {
      _controller->setPosition(PxExtendedVec3(position.x, position.y, position.z));
    };

    void SetDirectionVectors(glm::vec3 forwardVector, glm::vec3 rightVector, glm::vec3 upVector)
    {
      _forwardVector = forwardVector;
      _rightVector = rightVector;
      _upVector = upVector;
    }

    glm::vec3 GetPosition() const
    {
      PxExtendedVec3 position = _controller->getPosition();
      return glm::vec3(position.x, position.y, position.z);
    };

    void Move(glm::vec3 disp)
    {
      _controller->move(PxVec3(disp.x, disp.y, disp.z), 0.01f, (PxF32)(_currentTime - _lastMoveTime), PxControllerFilters());
      _lastMoveTime = _currentTime;
    };



    virtual void Update(double time)
    {
      if (_lastMoveTime == 0.0) _lastMoveTime = time;
      _lastFrameTime = _currentTime;
      _currentTime = time;
      _deltaTime = (float)(_currentTime - _lastFrameTime);

      _velocity += _deltaTime * _acceleration;
      _velocity *= _friction;
      _velocity = glm::clamp(_velocity, -_maxVelocity, _maxVelocity);
      Move(_velocity * _deltaTime);
    };

    virtual void DeliverMessage(string subject, MessageData data, KOK_Actor* sender)
    {
      if(subject == "translate")
        Move(data.v3);
      if(subject == "set velocity")
        _velocity = data.v3;

      if(subject == "apply velocity")
        _velocity += data.v3;

      if(subject == "apply x velocity")
      {
        _velocity += _rightVector * data.f;
      }

      if(subject == "apply y velocity")
      {
        _velocity += _upVector * data.f;
      }

      if(subject == "apply z velocity")
      {
        _velocity += _forwardVector * data.f;
      }

      if(subject == "set acceleration")
        _acceleration = data.v3;

      if(subject == "apply acceleration")
        _acceleration += data.v3;

      if(subject == "apply x acceleration")
      {
        _acceleration += _rightVector * data.f;
      }

      if(subject == "apply y acceleration")
      {
        _acceleration += _upVector * data.f;
      }

      if(subject == "apply z acceleration")
      {
        _acceleration += _forwardVector * data.f;
      }

      if(subject == "set x acceleration")
      {
        _acceleration = _rightVector * data.f;
      }

      if(subject == "set y acceleration")
      {
        _acceleration = _upVector * data.f;
      }

      if(subject == "set z acceleration")
      {
        _acceleration = _forwardVector * data.f;
      }

      if(subject == "set max velocity")
      {
        _maxVelocity = data.v3;
      }

      if(subject == "set friction")
      {
        _friction = data.v3;
      }
    };

    virtual void Draw()
    {

    };

  };

};

#endif

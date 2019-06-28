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

  public:
    KOK_PhysicsCharacter(KOK_PhysicsContext * physicsContext) : _physicsContext{physicsContext}
    {
      PxCapsuleControllerDesc desc;
      desc.height = 1.0f;
      desc.radius = 0.25f;
      desc.climbingMode = PxCapsuleClimbingMode::eEASY;

      PxControllerDesc* cDesc = &desc;

      cDesc->material = physicsContext->defaultMaterial;
      cDesc->position = PxExtendedVec3(0.0f,1.0f,0.0f);

      _controller = _physicsContext->characterManager->createController(*cDesc);
    };

    void SetPosition(glm::vec3 position)
    {
      _controller->setPosition(PxExtendedVec3(position.x, position.y, position.z));
    };

    glm::vec3 GetPosition() const
    {
      PxExtendedVec3 position = _controller->getPosition();
      return glm::vec3(position.x, position.y, position.z);
    };

    virtual void Update(double time)
    {

    };

    virtual void DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender)
    {

    };

    virtual void Draw()
    {

    };

  };

};

#endif

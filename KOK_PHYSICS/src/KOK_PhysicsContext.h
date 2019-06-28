#ifndef _DEBUG
#define _DEBUG //tells phys x that this is a debug build. Switch to NDEBUG in a release
#endif

#ifndef KOK_PHYSICSCONTEXT
#define KOK_PHYSICSCONTEXT

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "PxPhysicsAPI.h"
#include "KOK_VisualDebug.h"

using namespace std;
using namespace physx;

namespace KOK_Physics
{

  class KOK_PhysicsContext
  {
  private:
    PxDefaultErrorCallback gDefaultErrorCallback;
    PxDefaultAllocator gDefaultAllocatorCallback;

    PxFoundation * gFoundation;
    PxPhysics * gPhysics;
    PxDefaultCpuDispatcher * gDispatcher;

    PxScene * defaultScene;

    KOK_VisualDebug visualDebug;

  public:
PxControllerManager * characterManager;
PxMaterial * defaultMaterial;

    KOK_PhysicsContext();

    void StepPhysics(float step);
    void DrawDebugPhysics(glm::mat4 projection, glm::mat4 view);

    PxRigidDynamic * AddDynamicActor(float radius);
  };

};

#endif

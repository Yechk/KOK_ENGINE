#ifndef _DEBUG
#define _DEBUG //tells phys x that this is a debug build. Switch to NDEBUG in a release
#endif

#define GLM_ENABLE_EXPERIMENTAL

#include "stdlib.h"
#include <iostream>
#include "stdio.h"
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "PxPhysicsAPI.h"
#include "KOK_PhysicsContext.h"

#include "KOK_VisualDebug.h"

using namespace std;
using namespace physx;

namespace KOK_Physics
{

  KOK_PhysicsContext::KOK_PhysicsContext()
  {
    gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
    if(!gFoundation) cout << "failed PxCreateFoundation" << endl;

    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true);

    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    	gDispatcher = PxDefaultCpuDispatcherCreate(2);
    	sceneDesc.cpuDispatcher	= gDispatcher;
    	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
    	defaultScene = gPhysics->createScene(sceneDesc);
    	defaultMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

      //debug
      defaultScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
      defaultScene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
      defaultScene->setVisualizationParameter(PxVisualizationParameter::eBODY_AXES, 1.0f);
      defaultScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

    	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(PxVec3(0.0f,0.0f,0.0f), PxVec3(0.0f,1.0f,0.0f)), *defaultMaterial);
    	defaultScene->addActor(*groundPlane);

      characterManager = PxCreateControllerManager(*defaultScene);

    	//if(!interactive)
    	//	createDynamic(PxTransform(PxVec3(0,40,100)), PxSphereGeometry(10), PxVec3(0,-50,-100));
  };

  void KOK_PhysicsContext::StepPhysics(float step)
  {
    defaultScene->simulate(step);
    defaultScene->fetchResults(true);
  };

  void KOK_PhysicsContext::DrawDebugPhysics(glm::mat4 projection, glm::mat4 view)
  {
    vector<glm::vec3> lines;

    const PxRenderBuffer& rb = defaultScene->getRenderBuffer();
    for(PxU32 i=0; i < rb.getNbLines(); i++)
    {
        const PxDebugLine& line = rb.getLines()[i];
        lines.push_back(glm::vec3(line.pos0.x, line.pos0.y, line.pos0.z));
        lines.push_back(glm::vec3(line.pos1.x, line.pos1.y, line.pos1.z));
    }

    visualDebug.DrawDebug(lines, projection, view);
  };

  PxRigidDynamic * KOK_PhysicsContext::AddDynamicActor(float radius)
  {
    PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *defaultMaterial);
    PxRigidDynamic * dynamic = gPhysics->createRigidDynamic(PxTransform(PxVec3(0.0f, 3.0f, 0.0f)));
    shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
    dynamic->attachShape(*shape);
    PxRigidBodyExt::updateMassAndInertia(*dynamic, 10.0f);
    dynamic->setLinearVelocity(PxVec3(0.1f,0,0));

    dynamic->setActorFlag(PxActorFlag::eVISUALIZATION, true);

    defaultScene->addActor(*dynamic);

    shape->release();

    return dynamic;
  };
};

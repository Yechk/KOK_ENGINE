#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "KOK_Actor.h"
#include "KOK_Controller.h"
#include "KOK_Message.h"

#include "KOK_PhysicsContext.h"

#include "KOK_Model.h"
#include "KOK_Skeleton.h"
#include "KOK_Director.h"
#include "shader.h"
#include "KOK_Camera.h"
#include "KOK_ParticleSystem.h"

#include "KOK_EXT_CharacterBasic.h"
#include "KOK_PhysicsCharacter.h"

//include the enum for update hint flags (works in angelscript and c++)
#ifndef KOK_EXT_CHARACTERBASIC_HINTS
#define KOK_EXT_CHARACTERBASIC_HINTS
#define CHARACTER_HEADER_MODULE "HeaderModules/playerHeaderModule.as"
#include CHARACTER_HEADER_MODULE
#endif

using namespace std;

namespace KOK_CharacterBasic
{
  int KOK_EXT_CharacterBasic::currentInputFlags = 0;


  KOK_EXT_CharacterBasic::KOK_EXT_CharacterBasic(
    KOK_Graphics::KOK_RenderProcess * renderProcess,
    KOK_Physics::KOK_PhysicsContext * physicsContext,
    KOK_ScriptContext * scriptContext,
    KOK_PostOffice * globalOffice, GLFWwindow * window)
  {
    _physicsCharacter = new KOK_Physics::KOK_PhysicsCharacter(physicsContext);
    _renderProcess = renderProcess;
    _globalOffice = globalOffice;
    _localOffice = new KOK_PostOffice(32);
    _scriptContext = scriptContext;

    glfwSetKeyCallback(window, KeyCallback);
    currentInputFlags = 0;

    _camera = new KOK_Graphics::KOK_Camera();
    _up = glm::vec3(0,1,0);
    _camera->SetUp(_up);

    _forward = glm::vec3(0,0,1);
    _right = glm::vec3(-1,0,0);

    _controller = new KOK_ScriptedController(scriptContext, _localOffice, "playerUpdate.as",
      CHARACTER_HEADER_MODULE, "KOK_CharacterBasic");
  }

  void KOK_EXT_CharacterBasic::InitCharacter(string modelPath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale)
  {
    _characterModel = _renderProcess->AddModel(modelPath, location, scale, glm::vec3(0), rotation);
    _physicsCharacter->SetPosition(location);

    KOK_Graphics::KOK_Model * thisModel = _renderProcess->GetModelByIndex(_characterModel);
    _scriptContext->CacheComponents(thisModel, NULL,
      _physicsCharacter, _camera, NULL);

    _controller->RunInit();
  };

  void KOK_EXT_CharacterBasic::Update(double time)
  {
    KOK_Graphics::KOK_Model * thisModel = _renderProcess->GetModelByIndex(_characterModel);
    _scriptContext->CacheComponents(thisModel, NULL,
      _physicsCharacter, _camera, NULL);

    glm::vec3 currentPhysicsPosition = _physicsCharacter->GetPosition();

    glm::quat modelRot = thisModel->GetRotation();

    _forwardVector = _forward * modelRot;
    _rightVector = _right * modelRot;

    glm::vec3 camPosition = _forwardVector;
    float camFollowDistance = 5.0f;
    camPosition.x *= -camFollowDistance;
    camPosition.y += camFollowDistance;
    camPosition.z *= -camFollowDistance;

    _camera->SetTarget(glm::vec3(currentPhysicsPosition.x, currentPhysicsPosition.y +0.25f, currentPhysicsPosition.z));
    _camera->SetPosition(currentPhysicsPosition + camPosition);
    _camera->Update(time);
    _physicsCharacter->SetDirectionVectors(_forwardVector, _rightVector, _up);
    _physicsCharacter->Update(time);
    _controller->Update(time, currentInputFlags);

    _renderProcess->SetModelPositionByIndex(_characterModel, currentPhysicsPosition);
  };

  void KOK_EXT_CharacterBasic::DeliverMessage(string subject, MessageData data, KOK_Actor* sender)
  {

  };

  void KOK_EXT_CharacterBasic::Draw()
  {

  };

  void KOK_EXT_CharacterBasic::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
  {
    if(action == GLFW_PRESS)
    {
      switch (key)
      {
        case GLFW_KEY_W:
          currentInputFlags |= INPUT_FORWARD;
          break;

        case GLFW_KEY_S:
          currentInputFlags |= INPUT_BACK;
          break;

        case GLFW_KEY_A:
          currentInputFlags |= INPUT_LEFT;
          break;

        case GLFW_KEY_D:
          currentInputFlags |= INPUT_RIGHT;
          break;

        case GLFW_KEY_SPACE:
          currentInputFlags |= INPUT_JUMP;
          break;
      }
    }

    if(action == GLFW_RELEASE)
    {
      switch (key)
      {
        case GLFW_KEY_W:
          currentInputFlags &= ~INPUT_FORWARD;
          break;

        case GLFW_KEY_S:
          currentInputFlags &= ~INPUT_BACK;
          break;

        case GLFW_KEY_A:
          currentInputFlags &= ~INPUT_LEFT;
          break;

        case GLFW_KEY_D:
          currentInputFlags &= ~INPUT_RIGHT;
          break;

        case GLFW_KEY_SPACE:
          currentInputFlags &= ~INPUT_JUMP;
          break;
      }
    }
  }

}

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
  KOK_EXT_CharacterBasic::KOK_EXT_CharacterBasic(
    KOK_Graphics::KOK_RenderProcess * renderProcess,
    KOK_Physics::KOK_PhysicsContext * physicsContext,
    KOK_ScriptContext * scriptContext,
    KOK_PostOffice * globalOffice)
  {
    _physicsCharacter = new KOK_Physics::KOK_PhysicsCharacter(physicsContext);
    _renderProcess = renderProcess;
    _globalOffice = globalOffice;
    _localOffice = new KOK_PostOffice(32);
    _scriptContext = scriptContext;

    _camera = new KOK_Graphics::KOK_Camera();

    _controller = new KOK_ScriptedController(scriptContext, _localOffice, "playerInit.as", "playerUpdate.as",
      CHARACTER_HEADER_MODULE, "KOK_CharacterBasic");
  }

  void KOK_EXT_CharacterBasic::InitCharacter(string modelPath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale)
  {
    _characterModel = _renderProcess->AddModel(modelPath, location, scale, glm::vec3(0), rotation);
    _physicsCharacter->SetPosition(location);
  };

  void KOK_EXT_CharacterBasic::Update(double time)
  {
    _scriptContext->CacheComponents(_renderProcess->GetModelByIndex(_characterModel), NULL,
      _physicsCharacter, _camera, NULL);

    glm::vec3 currentPhysicsPosition = _physicsCharacter->GetPosition();

    _camera->SetTarget(glm::vec3(currentPhysicsPosition.x, currentPhysicsPosition.y +0.25f, currentPhysicsPosition.z));
    _camera->Update(time);
    _physicsCharacter->Update(time);
    _controller->Update(time, LOOP | INPUT_UP);
    _renderProcess->SetModelPositionByIndex(_characterModel, currentPhysicsPosition);
    _localOffice->Update(DUMP);
  };

  void KOK_EXT_CharacterBasic::DeliverMessage(string subject, MessageData data, KOK_Actor* sender)
  {

  };

  void KOK_EXT_CharacterBasic::Draw()
  {

  };

}

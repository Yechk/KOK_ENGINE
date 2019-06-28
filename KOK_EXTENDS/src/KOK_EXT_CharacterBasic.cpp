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

using namespace std;

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

  string headerModule =
  "enum Hints             "
  "{                      "
  "  LOOP = 0x00,         "
  "  INPUT_UP = 0x01,     "
  "  INPUT_DOWN = 0x02,   "
  "  INPUT_LEFT = 0x04,   "
  "  INPUT_RIGHT = 0x08,  "
  "  INPUT_JUMP = 0x10,   "
  "}                      ";

  _controller = new KOK_ScriptedController(scriptContext, _localOffice, "playerInit.as", "playerUpdate.as", headerModule);
}

void KOK_EXT_CharacterBasic::InitCharacter(string modelPath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale)
{
  _characterModel = _renderProcess->AddModel(modelPath, location, scale, glm::vec3(0), rotation);
  _physicsCharacter->SetPosition(location);
};

void KOK_EXT_CharacterBasic::Update(double time)
{
  _scriptContext->CacheComponents(_renderProcess->GetModelByIndex(_characterModel), NULL,
    _physicsCharacter, NULL, NULL);

  _physicsCharacter->Update(time);
  _controller->Update(time);
  _renderProcess->SetModelPositionByIndex(_characterModel, _physicsCharacter->GetPosition());
  _localOffice->Update(DUMP);
};

void KOK_EXT_CharacterBasic::DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender)
{

};

void KOK_EXT_CharacterBasic::Draw()
{

};

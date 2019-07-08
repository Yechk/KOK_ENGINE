#ifndef KOK_EXT_CHARACTERBASIC
#define KOK_EXT_CHARACTERBASIC

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
#include "KOK_PhysicsCharacter.h"

#include "KOK_Model.h"
#include "KOK_Skeleton.h"
#include "shader.h"
#include "KOK_Camera.h"
#include "KOK_ParticleSystem.h"
#include "KOK_Director.h"

using namespace std;

namespace KOK_CharacterBasic
{
  class KOK_EXT_CharacterBasic : public KOK_Actor
  {
  private:
    GLuint _characterModel;

    KOK_ScriptedController * _controller;
    KOK_Physics::KOK_PhysicsCharacter * _physicsCharacter;
    KOK_PostOffice * _localOffice;
    KOK_PostOffice * _globalOffice;
    KOK_Graphics::KOK_RenderProcess * _renderProcess;
    KOK_ScriptContext * _scriptContext;
    KOK_Graphics::KOK_Camera * _camera;

  public:
    KOK_EXT_CharacterBasic(KOK_Graphics::KOK_RenderProcess * renderProcess,
      KOK_Physics::KOK_PhysicsContext * physicsContext,
      KOK_ScriptContext * scriptContext, KOK_PostOffice * globalOffice);

    void InitCharacter(string modelPath, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale);

    void Update(double time);
    void DeliverMessage(string subject, MessageData data, KOK_Actor* sender);
    void Draw();

    KOK_Graphics::KOK_Camera * GetCamera() const
    {
      assert(_camera != NULL);
      return _camera;
    }
  };
}

#endif

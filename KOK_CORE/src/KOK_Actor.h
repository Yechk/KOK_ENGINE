#ifndef KOK_ACTOR
#define KOK_ACTOR

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;

union MessageData
{
  void* p;
  int i;
  uint ui;
  float f;
  double d;
  glm::vec3 v3;
  glm::vec4 v4;
  glm::quat q;
};

enum MessageSubject
{
  KOK_SUBJECT_POKE                       = 0,

  KOK_SUBJECT_WIDGET_LABEL_STRING        = 2,

	KOK_SUBJECT_WIDGET_LABEL_DOUBLE        = 3,
  KOK_SUBJECT_WIDGET_SLIDER_VALUE_UINT   = 3,

  KOK_SUBJECT_WIDGET_SLIDER_VALUE_FLOAT  = 4,

  KOK_SUBJECT_WIDGET_SLIDER_VALUE_RETURN = 5,

  KOK_SUBJECT_WIDGET_LABEL_UINT          = 10,
};

enum MessageComponentType
{
  KOK_COMPONENT_MESH,
  KOK_COMPONENT_SKELETON,
  KOK_COMPONENT_CONTROLLER,
  KOK_COMPONENT_PHYSICS
};

class KOK_Actor
{
public:
  string label = "DEFAULT";

  KOK_Actor() {label.resize(32, ' ');};
  KOK_Actor(string l) : KOK_Actor() { label = l;};

  virtual void Update(double time) = 0;
  virtual void DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender) = 0;
  virtual void Draw() = 0;
};

#endif

#ifndef KOK_ACTOR
#define KOK_ACTOR

#include <string>

using namespace std;

union MessageData
{
  void* p;
  int i;
  uint ui;
  float f;
  double d;
};

class KOK_Actor
{
public:
  string label = "DEFAULT";

  KOK_Actor() {label.resize(32, ' ');};
  KOK_Actor(string l) : KOK_Actor() { label = l;};

  virtual void Update(double time) = 0;
  virtual void DeliverMessage(unsigned long long subject, MessageData data, KOK_Actor* sender) = 0;
  virtual void Draw() = 0;
};

#endif

#ifndef KOK_CONTROLLER
#define KOK_CONTROLLER

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "angelscript.h"
#include "scriptstdstring.h"
#include "scriptbuilder.h"
#include "scripthandle.h"
#include "KOK_Actor.h"
#include "KOK_Message.h"

#include <iostream>

using namespace std;

/* TODO:
  - KOK_ScriptContext class will be registered as a singleton for the script engine. Actors will
    have a reference to it
  - Register enums for a message sending function sendmessage(COMPONENT_TYPE_ENUM, SUBJECT_ENUM, data)
  - completely decouples components from script engine

  -properties are accessed or set from a generic struct that is passed from the singleton (so there is no need to change context)
  -use define to add definitions at compile time for script to make get/set generic properties easier.


*/
//struct to hold script execution info

class KOK_ScriptContext
{
private:

  KOK_PostOffice * _cacheOffice;
  KOK_Actor * _cacheComponents[6];

  asIScriptContext * _context;
  asIScriptEngine * _engine;

  void MessageCallback(const asSMessageInfo *msg, void *param)
  {
    const char *type = "ERR ";
    if( msg->type == asMSGTYPE_WARNING )
      type = "WARN";
    else if( msg->type == asMSGTYPE_INFORMATION )
      type = "INFO";
    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
  };

  void RelayMessage(MessageSubject subject,
    MessageComponentType component, MessageFlag flag, MessageData data)
  {
    _cacheOffice->QueueMessage(subject, data, _cacheComponents[component],
      _cacheComponents[2], flag);
  }

  void RelayMessage(MessageSubject subject,
    MessageComponentType component, MessageFlag flag, int data)
  {
    MessageData _data;
    _data.i = data;

    RelayMessage(subject, component, flag, _data);
  }

  void RelayMessage(MessageSubject subject,
    MessageComponentType component, MessageFlag flag, float data)
  {
    MessageData _data;
    _data.f = data;

    RelayMessage(subject, component, flag, _data);
  }

  void RelayMessage(MessageSubject subject,
    MessageComponentType component, MessageFlag flag, float dataX,
    float dataY, float dataZ)
  {
    MessageData _data;
    _data.v3 = glm::vec3(dataX, dataY, dataZ);

    RelayMessage(subject, component, flag, _data);
  }

public:
  KOK_ScriptContext()
  {
    _engine = asCreateScriptEngine();

    int r = _engine->SetMessageCallback(asMETHOD(KOK_ScriptContext, MessageCallback),
              this, asCALL_THISCALL); assert(r >= 0);
    RegisterStdString(_engine);

    //enum for message subject
    _engine->RegisterEnum("MessageSubject");
    _engine->RegisterEnumValue("MessageSubject", "KOK_SUBJECT_POKE", 0);

    _engine->RegisterEnum("MessageFlag");
    _engine->RegisterEnumValue("MessageFlag", "BROADCAST", 0);
    _engine->RegisterEnumValue("MessageFlag", "URGENT", 1);
    _engine->RegisterEnumValue("MessageFlag", "EXPRESS", 2);
    _engine->RegisterEnumValue("MessageFlag", "MEDIA", 3);

    //enum for component types
    _engine->RegisterEnum("MessageComponentType");
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_MESH", 0);
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_SKELETON", 1);
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_CONTROLLER", 2);
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_PHYSICS", 3);
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_CAMERA", 4);
    _engine->RegisterEnumValue("MessageComponentType", "KOK_COMPONENT_AUX0", 5);

    _engine->RegisterGlobalFunction("void RelayMessage(MessageSubject subject, MessageComponentType component, MessageFlag flag, int data)",
      asMETHODPR(KOK_ScriptContext, RelayMessage, (MessageSubject,
        MessageComponentType, MessageFlag, int), void),
        asCALL_THISCALL_ASGLOBAL, this); assert(r>=0);

    _engine->RegisterGlobalFunction("void RelayMessage(MessageSubject subject, MessageComponentType component, MessageFlag flag, float data)",
      asMETHODPR(KOK_ScriptContext, RelayMessage, (MessageSubject,
        MessageComponentType, MessageFlag, float), void),
        asCALL_THISCALL_ASGLOBAL, this); assert(r>=0);

    _engine->RegisterGlobalFunction("void RelayMessage(MessageSubject subject, MessageComponentType component, MessageFlag flag, "
      "float dataX, float dataY, float dataZ)",
      asMETHODPR(KOK_ScriptContext, RelayMessage, (MessageSubject,
        MessageComponentType, MessageFlag, float, float, float), void),
        asCALL_THISCALL_ASGLOBAL, this); assert(r>=0);

    _context = _engine->CreateContext();
  };

  ~KOK_ScriptContext();

  asIScriptFunction * LoadScript(string path, string headerModule="")
  {
    //test the script
    CScriptBuilder builder;
    int r = builder.StartNewModule(_engine, "module");
    if(r > 0)
    {
      cout << "ERROR STARTING NEW MODULE" << endl;
    }
    string concatenatedPath = "./Scripts/" + path;
    if(headerModule != "")
    {
      r = builder.AddSectionFromFile(headerModule.c_str());
      if(r < 0)
      {
        cout << "HEADER MODULE ERROR" << endl;
      }
    }
    r = builder.AddSectionFromFile(concatenatedPath.c_str());
    if(r < 0)
    {
      cout << "SCRIPT ERRORS" << endl;
    }
    r = builder.BuildModule();
    if(r < 0)
    {
      cout << "SCRIPT COMPILATION ERROR" << endl;
    }

    asIScriptModule *mod = _engine->GetModule("module");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main(int hint)");
    if(func == 0)
    {
      cout << "Yo homie you better add a main() function to that script." << endl;
    }

    return func;
  };

  void CacheComponents(KOK_Actor * cacheMesh, KOK_Actor * cacheSkeleton,
    KOK_Actor * cachePhysics, KOK_Actor * cacheCamera, KOK_Actor * cacheAux0)
  {
    _cacheComponents[0] = cacheMesh;
    _cacheComponents[1] = cacheSkeleton;
    _cacheComponents[3] = cachePhysics;
    _cacheComponents[4] = cacheCamera;
    _cacheComponents[5] = cacheAux0;
  }

  void RunScript(asIScriptFunction * info, KOK_PostOffice * cacheOffice, KOK_Actor * cacheController, int hint)
  {
    _cacheOffice = cacheOffice;
    _cacheComponents[2] = cacheController;

    _context->Prepare(info);
    _context->SetArgDWord(0, hint);

    int rt = _context->Execute();
    if(rt != asEXECUTION_FINISHED)
    {
      if(rt == asEXECUTION_EXCEPTION)
      {
        cout << "aw shiiit. Script exception: " << _context->GetExceptionString() << endl;
      }
    }
  };


  void Init();
};

class KOK_Controller : public KOK_Actor
{
public:
  KOK_PostOffice * localOffice;

  KOK_Controller() {};

  KOK_Controller(KOK_PostOffice * _localOffice) : localOffice{_localOffice} {};

  virtual void Update(double time)
  {
    localOffice->Update(MARCH);
  };

  virtual void DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender)
  {

  };

  virtual void Draw()
  {

  };

};

class KOK_ScriptedController : public KOK_Controller
{
private:
  KOK_ScriptContext * _scriptContext;
  asIScriptFunction * _initScript;
  asIScriptFunction * _updateScript;

public:

  KOK_ScriptedController() {};

  KOK_ScriptedController(KOK_ScriptContext * scriptContext, KOK_PostOffice * _localOffice,
    string initPath="", string updatePath="", string headerModule="") : _scriptContext{scriptContext}
  {
    localOffice = _localOffice;
    _updateScript = NULL;

    if(initPath != "")
    {
      _initScript = _scriptContext->LoadScript(initPath);
      _scriptContext->RunScript(_initScript, localOffice, this, 0);
    }

    if(updatePath != "")
    {
      _updateScript = _scriptContext->LoadScript(updatePath, headerModule);
    }
  };

  KOK_ScriptedController(KOK_ScriptContext * scriptContext, KOK_PostOffice * _localOffice,
     asIScriptFunction * initScript, asIScriptFunction * updateScript) : _scriptContext{scriptContext}
  {
    localOffice = _localOffice;
    _updateScript = NULL;

    if(initScript != NULL)
    {
      _initScript = initScript;
      _scriptContext->RunScript(_initScript, localOffice, this, 0);
    }

    if(updateScript != NULL)
    {
      _updateScript = updateScript;
    }
  };

  virtual void Update(double time)
  {
    if(_updateScript != NULL) _scriptContext->RunScript(_updateScript, localOffice, this, 0);
    KOK_Controller::Update(time);
  };

  virtual void DeliverMessage(uint64_t subject, MessageData data, KOK_Actor* sender)
  {
    if (subject == KOK_SUBJECT_POKE)
    {
      cout << "KOK_ScriptedController was poked: " << data.i << endl;
    }
  };

  virtual void Draw()
  {

  };

  void ReloadInit(string path)
  {
    if(_initScript != NULL) _initScript->Release();
    _initScript = _scriptContext->LoadScript(path);
    _scriptContext->RunScript(_initScript, localOffice, this, 0);
  }

  void RunScript(GLuint hint)
  {
    if(_updateScript != NULL) _scriptContext->RunScript(_updateScript, localOffice, this, hint);
  }
};

#endif

namespace KOK_CharacterBasic
{
  const float forwardAcceleration = 1.5f;
  const float backwardAcceleration = -1.5f;
  const float lateralAcceleration = 1.5f;

  void Init(int hint)
  {
    RelayMessage("set max velocity", KOK_COMPONENT_PHYSICS, URGENT, 150.0f,150.0f,150.0f);
    RelayMessage("set friction", KOK_COMPONENT_PHYSICS, URGENT, 0.9f, 0.9f, 0.9f);

    RelayMessage("set y acceleration", KOK_COMPONENT_PHYSICS, URGENT, -9.8f);
  }

  void Update(int hint)
  {
    if(CheckHint(hint, INPUT_FORWARD))
    {
      RelayMessage("apply z velocity", KOK_COMPONENT_PHYSICS, URGENT, forwardAcceleration);
    }

    if(CheckHint(hint, INPUT_BACK))
    {
      RelayMessage("apply z velocity", KOK_COMPONENT_PHYSICS, URGENT, backwardAcceleration);
    }

    if(CheckHint(hint, INPUT_LEFT))
    {
      RelayMessage("apply x velocity", KOK_COMPONENT_PHYSICS, URGENT, -lateralAcceleration);
    }

    if(CheckHint(hint, INPUT_RIGHT))
    {
      RelayMessage("apply x velocity", KOK_COMPONENT_PHYSICS, URGENT, lateralAcceleration);
    }
  }
}

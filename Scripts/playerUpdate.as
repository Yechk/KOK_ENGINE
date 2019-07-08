namespace KOK_CharacterBasic
{
  void main(int hint)
  {
    if(CheckHint(hint, INPUT_UP))
    {
      RelayMessage("move", KOK_COMPONENT_PHYSICS, URGENT, 0.0f,0.0f,0.015f);
    }
  }
}

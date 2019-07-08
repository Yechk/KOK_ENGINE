namespace KOK_CharacterBasic
{
  enum Hints
  {
    LOOP = 0x00,
    INPUT_UP = 0x01,
    INPUT_DOWN = 0x02,
    INPUT_LEFT = 0x04,
    INPUT_RIGHT = 0x08,
    INPUT_JUMP = 0x10,
  };

  bool CheckHint(int val, int hint)
  {
    if(val & hint == hint) return true;
    return false;
  };
};

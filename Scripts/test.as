void main(int hint)
{
  //send a poke message to controller
  RelayMessage(KOK_SUBJECT_POKE, KOK_COMPONENT_CONTROLLER, URGENT, hint);
}

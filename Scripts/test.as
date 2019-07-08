void main(int hint)
{
  //send a poke message to controller
  RelayMessage("poke", KOK_COMPONENT_CONTROLLER, URGENT, hint);
}

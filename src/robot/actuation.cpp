Actuation::Actuation(uint8_t _clawPin, uint8_t _wristPin, uint8_t _liftPin, uint8_t _topPin, uint8_t _botPin)
{
 clawPin  = _clawPin;
 wristPin = _wristPin;
 liftPin  = _liftPin;
 topPin   = _topPin;
 bootPin  = _bootPin;
}


void Actuation::changeClawState(actState nextState)
{
 desiredClawState = nextState;
} 
void Actuation::changeLiftState(actState nextState);
{
 desiredLiftState = nextState;
}

bool Actuation::moveUp()
{
 if(currentLiftState != UP)
 {
  analogWrite(liftPin, GOUP);
  return 0;
 }
 else
 {
  analogWrite(liftPin, STILL);
  analogWrite(wristPin, FACEUP);
  return 1;
 }
}
//this needs to be different because it is should already start rotating down, we will have to call this in the middle of a move 
bool Actuation::moveDown()
{
 if(currentLiftState != DOWN)
 {
  analogWrite(liftPin, GODOWN);
  analogWrite(wristPin, FACEDOWN);
  return 0;
 }
 else
 {
  analogWrite(liftPin, STILL);
  return 1;
 }
} 
//attach these to the limit switch interupts
void Actuation::downReach()
{ 
 currentLiftState = DOWN;
}
void Actuation::upReach()
{
 currentLiftState = UP;
}

void Actuation::closeClaw()
{
 analogWrite(clawPin, CLOSE);
}
void Actuation::OpenClaw()
{
 analogWrite(clawPin, OPEN);
}

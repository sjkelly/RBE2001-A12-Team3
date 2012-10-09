#include "actuation.h"


Actuation::Actuation(Servo* _clawServo, Servo* _wristServo, Servo* _liftServo, uint8_t _topPin, uint8_t _botPin)
{
 clawServo = _clawServo;
 wristServo = _wristServo;
 liftServo = _liftServo;
 topPin   = _topPin;
 botPin  = _botPin;
}

bool Actuation::moveUp()
{
 if(currentLiftState != UP)
 {
  liftServo->write( GOUP);
  return 0;
 }
 else
 {
  liftServo->write( STILL);
  wristServo->write(FACEUP);
  return 1;
 }
}
//this needs to be different because it is should already start rotating down, we will have to call this in the middle of a move 
bool Actuation::moveDown()
{
 if(currentLiftState != DOWN)
 {
  liftServo->write( GODOWN);
  wristServo->write(FACEDOWN);
  return 0;
 }
 else
 {
  liftServo->write( STILL);
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
 clawServo->write( CLOSE);
}
void Actuation::openClaw()
{
 clawServo->write( OPEN);
}

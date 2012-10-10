#include "Arduino.h"
#include "actuation.h"


Actuation::Actuation(Servo* _clawServo, Servo* _wristServo, Servo* _liftServo, uint8_t _topPin, uint8_t _botPin)
{
 clawServo = _clawServo;
 wristServo = _wristServo;
 liftServo = _liftServo;
 topPin   = _topPin;
 botPin  = _botPin;
 currentClaw = START_CLAW;
 desiredClaw = START_CLAW;
 //currentLiftState = MID;
}

uint8_t Actuation::moveUp()
{
 if(currentLiftState != UP)
 {
  liftServo->write( GOUP);
  wristServo->write(FACEDOWN);
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
uint8_t Actuation::moveDown()
{
 if(currentLiftState != DOWN)
 {
  liftServo->write(GODOWN);
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
/*
void Actuation::midReach()
{
 currentLiftState = MID;
}*/

void Actuation::closeClaw()
{
 desiredClaw = CLOSED;
}
void Actuation::openClaw()
{
 desiredClaw = OPENED;
}

void Actuation::updateClaw()
{
  if(desiredClaw != currentClaw)
  {
   if(desiredClaw == CLOSED)
    clawServo->write( CLOSE);
   else
    clawServo->write( OPEN);
   delay(SERVO_RESPONSE);
   currentClaw = desiredClaw;
  }
}

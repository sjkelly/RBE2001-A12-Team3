#include "move.h"


Motor::Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA, bool _reverse)
{
 pinMode(_oneA, OUTPUT);
 pinMode(_twoA, OUTPUT);
 encPin = _encPin;
 drivePin = _drivePin;
 reverse = _reverse;
 oneA = _oneA;
 twoA = _twoA;
 //attachInterrupt(_encPin, log, RISING);
}
 
void Motor::drive(int16_t speed)
{
 if(speed > 0)
 {
  digitalWrite(oneA, 0);
  digitalWrite(twoA, 1);
 }
 else
 {
  speed *= -1;
  digitalWrite(twoA, 0);
  digitalWrite(oneA, 1);
 }
 analogWrite(drivePin, speed);
}
void Motor::log()
{
 if(speed > 0)
  ticks++;
 else
  ticks--;
}



namespace Move
{
  volatile uint8_t bumperHit;
  volatile uint32_t leftCount = 0;
  volatile uint32_t rightCount = 0;
  
  void followLine(int16_t speed, uint8_t leftSensor, uint8_t midSensor, uint8_t rightSensor, Motor right, Motor left)
  {
   if(!leftSensor&&midSensor&&!rightSensor)
   {
    left.drive(speed);
    right.drive(speed);
   }
   else if(rightSensor)
   {
    right.drive(speed);
    left.drive(speed*LEFT_LINE_FOLLOW_PROP);
   }
   else if(leftSensor)
   {
    left.drive(speed);
    right.drive(speed*RIGHT_LINE_FOLLOW_PROP);
   }
  }
  
}

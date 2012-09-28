#include "move.h"


Motor::Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA, bool _reverse)
{
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

void followLine(int16_t speed, bool leftSensor, bool midSensor, bool rightSensor, Motor right, Motor left)
{
 if(midSensor)
 {
  left.drive(speed);
  right.drive(speed);
 }
 else if(rightSensor)
 {
  right.drive(speed);
  left.drive(0);
 }
 else if(leftSensor)
 {
  left.drive(speed);
  right.drive(0);
 }
}

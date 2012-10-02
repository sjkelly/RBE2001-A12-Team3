#include "motor.h"

Motor::Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA, bool _reverse)
{
 pinMode(_oneA, OUTPUT);
 pinMode(_twoA, OUTPUT);
 encPin = _encPin;
 drivePin = _drivePin;
 reverse = _reverse;
 oneA = _oneA;
 twoA = _twoA;
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

float Motor::getDistance(void){
  return (float)count/ENCODER_CPR*2*PI*WHEEL_RADIUS_CM;
}


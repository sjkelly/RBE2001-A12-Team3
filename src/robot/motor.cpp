#include "motor.h"

Motor::Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA, float _prop)
{
 pinMode(_oneA, OUTPUT);
 pinMode(_twoA, OUTPUT);
 pinMode(_encPin, INPUT);
 encPin = _encPin;
 drivePin = _drivePin;
 oneA = _oneA;
 twoA = _twoA;
 count = 0;
 proportion = _prop;
 interruptPin = (encPin == 2)?0:(encPin == 3)?1:(encPin == 21)?2:(encPin == 20)?3:(encPin == 19)?4:(encPin == 18)?5:0;
}
 
void Motor::drive(int16_t speed)
{
 if(speed > 0)
 {
  digitalWrite(oneA, 0);
  digitalWrite(twoA, 1);
 }
 else if(speed < 0)
 {
  speed *= -1;
  digitalWrite(twoA, 0);
  digitalWrite(oneA, 1);
 }
 else if(speed == 0)
 {
  digitalWrite(twoA, 0);
  digitalWrite(oneA, 0);
 }
 analogWrite(drivePin, speed);
}

double Motor::getDistance(void){
  return (double)count/ENCODER_CPR*2*PI*WHEEL_RADIUS_CM;
}

void Motor::resetDistance(void){
  count = 0;
}

#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "robot.h"

class Motor
{
 private:
  uint8_t speed;
  int8_t drivePin, encPin, oneA, twoA;
 public:
  Motor();
  Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA);
  void drive(int16_t speed);
  float getDistance(void);
  void encoderISR();
  int32_t count;
  uint8_t interruptPin;
};


#endif

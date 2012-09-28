#ifndef __MOVEH__
#define __MOVEH__
#define HBRIDGE1 3
#define HBRIDGE2 4
#define ENABLE 5
#include "Arduino.h"
#include <stdlib.h>

class Motor
{
 private:
  int16_t ticks;
  uint8_t speed;
  bool reverse;
  int8_t drivePin, encPin, oneA, twoA;
 public:
  Motor(int8_t _encPin, int8_t _drivePin, int8_t _oneA, int8_t _twoA, bool _reverse);
  void drive(int16_t speed);
  void log();
};
//namespace move
//{

void followLine(int16_t speed, int leftSensor, int midSensor, int rightSensor, Motor, Motor);  

#endif

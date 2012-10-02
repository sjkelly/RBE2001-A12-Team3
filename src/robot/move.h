#ifndef __MOVEH__
#define __MOVEH__
#include "Arduino.h"
#include <stdlib.h>
#include "robot.h"

#define HBRIDGE1 3
#define HBRIDGE2 4
#define ENABLE 5

//Tuning Defines
#define RIGHT_LINE_FOLLOW_PROP 0.7
#define LEFT_LINE_FOLLOW_PROP 0.5

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

namespace Move
{
  volatile extern uint8_t bumperHit;
  volatile extern uint32_t leftCount, rightCount;
  void followLine(int16_t speed, uint8_t leftSensor, uint8_t midSensor, uint8_t rightSensor, Motor, Motor);  
  float getLeftDistance(void);
  float getRightDistance(void);
}

#endif


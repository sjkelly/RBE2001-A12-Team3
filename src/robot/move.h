#ifndef __MOVEH__
#define __MOVEH__
#include "Arduino.h"
#include "robot.h"
#include "motor.h"

namespace Move
{
  volatile extern uint8_t bumperHit;
  extern uint8_t atIntersection;
  extern float currentPosition[2];  //(x,y)
  void followLine(int16_t speed, uint8_t leftSensor, uint8_t midSensor, uint8_t rightSensor, Motor, Motor);  
}

#endif


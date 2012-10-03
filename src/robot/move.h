#ifndef __MOVEH__
#define __MOVEH__
#include "Arduino.h"
#include "robot.h"
#include "motor.h"
#include "linesensor.h"


class Move
{
  public:
  uint8_t atIntersection;
  float currentPosition[2];  //(x,y)
  
  Move(uint8_t,LineSensor&, Motor&, Motor&);
  void followLine(int16_t speed);
  uint8_t checkBumper(void);
  void turn180(int16_t);
  void turnRight(int16_t);
  void turnLeft(int16_t);  
  
  private:
  LineSensor& lineSensor;
  Motor& leftMotor; 
  Motor& rightMotor;
  uint8_t bumperPin;
};

#endif


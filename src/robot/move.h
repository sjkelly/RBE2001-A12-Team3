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
  void turn180(void);
  void turnRight(void);
  void turnLeft(void);  
  
  private:
  Motor& leftMotor; 
  Motor& rightMotor;
  LineSensor& lineSensor;
  uint8_t bumperPin;
};

#endif


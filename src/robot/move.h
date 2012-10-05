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
  uint8_t followLine(int16_t speed);
  uint8_t checkBumper(void);
  void turn180(int16_t);
  void turnRight(int16_t);
  void turnLeft(int16_t);  
  void forward(double, int16_t, uint8_t);
  void to(double, double, int16_t);
  private:
  LineSensor& lineSensor;
  Motor& leftMotor; 
  Motor& rightMotor;
  uint8_t bumperPin;
};

#endif


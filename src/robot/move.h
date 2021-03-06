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
  uint8_t currentPosition;  //(x,y)
  
  Move(uint8_t,LineSensor*, Motor*, Motor*);
  uint8_t followLine(int16_t speed);
  uint8_t checkBumper(void);
  uint8_t turn(int16_t, int16_t); //takes angle from -180 to 180 and speed
  uint8_t forward(double, int16_t, uint8_t);
  
  /*Takes character representing destination.
   * A and B are reactor tubes. 1-4 is spent rods
   * 4-5 are New rods. 
   */
  uint8_t to(uint8_t, int16_t); 
  private:
  LineSensor* lineSensor;
  Motor* leftMotor; 
  Motor* rightMotor;
  uint8_t bumperPin;
  uint8_t turning, drivingForward, moving; //state transition and terminators. 
  int16_t turnTarget;
  
  volatile uint8_t crossedLines;
  volatile double avgDistance;
  volatile double startDistance;
  
  uint8_t acceptingCrosses;
};

#endif


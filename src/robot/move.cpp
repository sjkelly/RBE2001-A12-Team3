#include "move.h"

namespace Move
{
  volatile uint8_t bumperHit = 0;
  uint8_t atIntersection = 0;
  
  float currentPosition[2] = {0,0};
  
  void followLine(int16_t speed, uint8_t leftSensor, uint8_t midSensor, uint8_t rightSensor, Motor right, Motor left)
  {
   if(!leftSensor&&midSensor&&!rightSensor)
   {
    left.drive(speed);
    right.drive(speed);
    atIntersection = 0;
   }
   else if(leftSensor&&midSensor&&rightSensor){
    left.drive(speed);
    right.drive(speed); 
    atIntersection = 1;
   }
   else if(rightSensor)
   {
    right.drive(speed);
    left.drive(speed*LEFT_LINE_FOLLOW_PROP);
    atIntersection = 0;
   }
   else if(leftSensor)
   {
    left.drive(speed);
    right.drive(speed*RIGHT_LINE_FOLLOW_PROP);
    atIntersection = 0;
   }
  }
  
  uint8_t checkBumper(void){
    return digitalRead(BUMPER_PIN);
  }
}

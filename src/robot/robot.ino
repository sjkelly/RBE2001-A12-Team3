#include "robot.h"
#include "linesensor.h"
#include "move.h"


lineSensor myLineSensor;
Motor leftMotor(19,8,33,34,1);
Motor rightMotor(29,9,35,36,1);

void setup(){
  Serial.begin(9600);
}

void loop(){
  if(DEBUG){
    myLineSensor.print();
  }
  myLineSensor.update();
  followLine(125, myLineSensor.frontLeft, myLineSensor.frontRight, myLineSensor.frontCenter, rightMotor, leftMotor);
}


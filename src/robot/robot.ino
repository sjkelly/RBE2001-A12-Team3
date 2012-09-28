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
  myLineSensor.update();
  if(DEBUG)myLineSensor.print();
  leftMotor.drive(255);
  followLine(255, myLineSensor.sensor[0], myLineSensor.sensor[1], myLineSensor.sensor[2], rightMotor, leftMotor);
}

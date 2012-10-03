#include "move.h"

Move::Move(uint8_t _bumperPin, LineSensor& _lineSensor, Motor& _leftMotor, Motor& _rightMotor):
  lineSensor(_lineSensor) ,
  leftMotor(_leftMotor) ,
  rightMotor(_rightMotor) 
{
  pinMode(_bumperPin, INPUT);
  digitalWrite(_bumperPin, HIGH);       // turn on pullup resistors for our switch
  bumperPin = _bumperPin;
  atIntersection = 0;
  currentPosition[0] = 0;
  currentPosition[1] = 1;
}

void Move::followLine(int16_t speed)
{
 if(!lineSensor.frontLeft&&lineSensor.frontCenter&&!lineSensor.frontRight)
 {
  leftMotor.drive(speed);
  rightMotor.drive(speed);
  atIntersection = 0;
 }
 else if(lineSensor.frontLeft&&lineSensor.frontCenter&&lineSensor.frontRight){
  leftMotor.drive(speed);
  rightMotor.drive(speed); 
  atIntersection = 1;
 }
 else if(lineSensor.frontLeft)
 {
  rightMotor.drive(speed);
  leftMotor.drive(speed*LEFT_LINE_FOLLOW_PROP);
  atIntersection = 0;
 }
 else if(lineSensor.frontRight)
 {
  leftMotor.drive(speed);
  rightMotor.drive(speed*RIGHT_LINE_FOLLOW_PROP);
  atIntersection = 0;
 }
}

uint8_t Move::checkBumper(void){
  return digitalRead(bumperPin);
}

void Move::turn180(int16_t speed){
  float targetDistance = WHEEL_SPACING_CM*PI/2;
  if(leftMotor.getDistance()<targetDistance) leftMotor.drive(speed);
  else leftMotor.drive(0);
  if(rightMotor.getDistance()<targetDistance) rightMotor.drive(speed*-1);
  else rightMotor.drive(0); 
}
void Move::turnRight(int16_t speed){
  float targetDistance = WHEEL_SPACING_CM*PI/4;   
  if(leftMotor.getDistance()<targetDistance) leftMotor.drive(speed*-1);
  else leftMotor.drive(0);
  if(rightMotor.getDistance()<targetDistance) rightMotor.drive(speed);
  else rightMotor.drive(0);  
}
void Move::turnLeft(int16_t speed){
  float targetDistance = WHEEL_SPACING_CM*PI/4;
  if(leftMotor.getDistance()<targetDistance) leftMotor.drive(speed);
  else leftMotor.drive(0);
  if(rightMotor.getDistance()<targetDistance) rightMotor.drive(speed*-1);
  else rightMotor.drive(0);  
}


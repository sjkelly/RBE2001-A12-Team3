#include "move.h"

Move::Move(uint8_t _bumperPin, LineSensor* _lineSensor, Motor* _leftMotor, Motor* _rightMotor)
{
  pinMode(_bumperPin, INPUT);
  digitalWrite(_bumperPin, HIGH);       // turn on pullup resistors for our switch
  bumperPin = _bumperPin;
  atIntersection = 0;
  currentPosition[0] = 0;
  currentPosition[1] = 0;
  lineSensor = _lineSensor;
  leftMotor = _leftMotor;
  rightMotor = _rightMotor;
}

uint8_t Move::followLine(int16_t speed)
{
 lineSensor->update();
 if(!lineSensor->frontLeft&&lineSensor->frontCenter&&!lineSensor->frontRight)
 {
  leftMotor->drive(speed);
  rightMotor->drive(speed);
 }
 else if(lineSensor->frontLeft&&lineSensor->frontCenter&&lineSensor->frontRight&&lineSensor->wingRight&&lineSensor->wingLeft){
  leftMotor->drive(speed);
  rightMotor->drive(speed); 
  if(lineSensor->consecutiveStates > LINE_SENSOR_CONSECUTIVE_READS){
    lineSensor->consecutiveStates = 0;
    return 1;
  }
 }
 else if(lineSensor->frontLeft&&lineSensor->frontCenter&&!lineSensor->frontRight)
 {
  rightMotor->drive(speed);
  leftMotor->drive(0);
 }
 else if(!lineSensor->frontRight&&lineSensor->frontCenter&&lineSensor->frontRight)
 {
  leftMotor->drive(speed);
  rightMotor->drive(0);
 }
 else if(lineSensor->frontLeft&&!lineSensor->frontCenter&&!lineSensor->frontRight)
 {
  rightMotor->drive(speed);
  leftMotor->drive(speed/2);
 }
 else if(!lineSensor->frontRight&&!lineSensor->frontCenter&&lineSensor->frontRight)
 {
  leftMotor->drive(speed);
  rightMotor->drive(speed/2);
 }
 /*else {
   leftMotor->drive(speed);
   rightMotor->drive(speed);
 }*/
 return 0;
}

uint8_t Move::checkBumper(void){
  return !digitalRead(bumperPin);
}

void Move::turn180(int16_t speed){
 leftMotor->resetDistance();
 rightMotor->resetDistance();
 while(leftMotor->getDistance()<=DISTANCE180 && rightMotor->getDistance()<=DISTANCE180){
   leftMotor->drive(speed*-1);
   rightMotor->drive(speed);
 }
 rightMotor->drive(0);  
 leftMotor->drive(0); 
 if(DEBUG)Serial.println("Turn 180 finished!"); 
}

void Move::turnRight(int16_t speed){ 
 leftMotor->resetDistance();
 rightMotor->resetDistance();
 while(leftMotor->getDistance()<=DISTANCE90 && rightMotor->getDistance()<=DISTANCE90)
 {
   leftMotor->drive(speed);
   rightMotor->drive(speed*-1);
 }
 rightMotor->drive(0);  
 leftMotor->drive(0); 
 if(DEBUG)Serial.println("Turn right finished!");
}

void Move::turnLeft(int16_t speed){
 leftMotor->resetDistance();
 rightMotor->resetDistance();
 while(leftMotor->getDistance()<=DISTANCE90 && rightMotor->getDistance()<=DISTANCE90)
 {
   if(leftMotor->getDistance()<=DISTANCE90)leftMotor->drive(speed*-1);
   else leftMotor->drive(0);
   if(rightMotor->getDistance()<=DISTANCE90)rightMotor->drive(speed);
   else rightMotor->drive(0);
   if(lineSensor->rearCenter && lineSensor->consecutiveStates > LINE_SENSOR_CONSECUTIVE_READS) break;
 }
 rightMotor->drive(0);  
 leftMotor->drive(0); 
 if(DEBUG)Serial.println("Turn left finished!");
}

void Move::forward(double target, int16_t speed, uint8_t allowedCrosses){
  leftMotor->resetDistance();
  rightMotor->resetDistance();
  volatile uint8_t crossedLines = 0;
  volatile double avgDistance = 0;
  volatile double startDistance = 0;
  while(avgDistance<target)
  {
    if(followLine(speed)){
      startDistance = avgDistance;
      while(avgDistance < (startDistance + target/20)){
        followLine(speed);
        avgDistance = leftMotor->getDistance()/2+rightMotor->getDistance()/2;  
      }
      crossedLines++;
    }
    avgDistance = leftMotor->getDistance()/2+rightMotor->getDistance()/2;
    if((crossedLines > allowedCrosses && avgDistance > target/10) || checkBumper()) break;
  }
  leftMotor->drive(0);
  rightMotor->drive(0);
  if(DEBUG)Serial.println("Forward move finished!");
}

void Move::to(double targetX, double targetY, int16_t speed){
  if(targetX == currentPosition[0] && targetY == currentPosition[1]) return;
  
  //we will always want to backout and turn around
  forward(20,-speed, 1); 
  turn180(speed);
  uint8_t moves;
  
  if(currentPosition[0] == targetX) moves = 1; //on the long line
  else if(currentPosition[1] == targetY) moves = 1; //going across field
  else if(targetX == 0) moves = 2;  //going to the center 
  else if(currentPosition[0] == 0) moves = 2; //in the center going elsewhere
  else moves = 3;
  
  if(DEBUG){
    Serial.print("Making ");
    Serial.print(moves);
    Serial.println(" moves");
  }
  if(moves == 1){
    if(currentPosition[0] == targetX)forward(FIELD_Y, speed, 4);
    else if(currentPosition[1] == targetY)forward(FIELD_X, speed, 1);
  }
  else if(moves == 2){
    
    
  }
  else if(moves == 3){
    
    
    
  }
  
}

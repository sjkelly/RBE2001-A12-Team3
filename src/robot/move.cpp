#include "move.h"

Move::Move(uint8_t _bumperPin, LineSensor* _lineSensor, Motor* _leftMotor, Motor* _rightMotor)
{
  pinMode(_bumperPin, INPUT);
  digitalWrite(_bumperPin, HIGH);       // turn on pullup resistors for our switch
  bumperPin = _bumperPin;
  atIntersection = 0;
  currentPosition = 'A';
  lineSensor = _lineSensor;
  leftMotor = _leftMotor;
  rightMotor = _rightMotor;
}

uint8_t Move::followLine(int16_t speed)
{
 lineSensor->update();
 if(!lineSensor->frontLeft&&!lineSensor->frontCenter&&!lineSensor->frontRight)
 {
  leftMotor->drive(speed);
  rightMotor->drive(speed);
 }
 else if(!lineSensor->frontLeft&&!lineSensor->frontCenter&&lineSensor->frontRight){
  leftMotor->drive(speed*0.9);
  rightMotor->drive(speed*0.5);
 }
 else if(!lineSensor->frontLeft&&lineSensor->frontCenter&&!lineSensor->frontRight){
  leftMotor->drive(speed);
  rightMotor->drive(speed);
 }
 else if(!lineSensor->frontLeft&&lineSensor->frontCenter&&lineSensor->frontRight){
  leftMotor->drive(speed*0.8);
  rightMotor->drive(speed*0.6);
 }
 else if(lineSensor->frontLeft&&!lineSensor->frontCenter&&!lineSensor->frontRight){
  leftMotor->drive(speed*0.5);
  rightMotor->drive(speed*0.9);
 }
 else if(lineSensor->frontLeft&&lineSensor->frontCenter&&!lineSensor->frontRight){
  leftMotor->drive(speed*0.6);
  rightMotor->drive(speed*0.8);
 }
 else if(lineSensor->frontLeft&&lineSensor->frontCenter&&lineSensor->frontRight&&lineSensor->wingRight&&lineSensor->wingLeft){
  leftMotor->drive(speed);
  rightMotor->drive(speed); 
  if(lineSensor->consecutiveStates >= LINE_SENSOR_CONSECUTIVE_READS){
    lineSensor->consecutiveStates = 0;
    return 1;
  }
 }
 return 0;
}

uint8_t Move::checkBumper(void){
  return !digitalRead(bumperPin);
}

uint8_t Move::turn(int16_t angle, int16_t speed){
 if(!turning){
   leftMotor->resetDistance(); 
   rightMotor->resetDistance();
   turning = 1; //we are now turning
   turnTarget = abs(WHEEL_SPACING_CM*PI*angle/360); //find our arc length target
 }
 if(turning && leftMotor->getDistance()<=turnTarget && rightMotor->getDistance()<=turnTarget){
   if(angle > 0){
     leftMotor->drive(speed*-1);
     rightMotor->drive(speed);
   }
   else if(angle < 0){
     leftMotor->drive(speed);
     rightMotor->drive(speed*-1);
   }
   return 0;
 }
 else {
   rightMotor->drive(0);  
   leftMotor->drive(0); 
   if(DEBUG)Serial.println("Turn 180 finished!");
   turning = 0;
   turnTarget = 0;
   return 1;
 } 
}

uint8_t Move::forward(double target, int16_t speed, uint8_t allowedCrosses){
  if(!drivingForward){
    leftMotor->resetDistance();
    rightMotor->resetDistance();
    drivingForward = 1;
    crossedLines = 0;
    avgDistance = 0;
    startDistance = 0;
    acceptingCrosses = 1;
  }
  if(drivingForward && avgDistance<target)
  {
    if(followLine(speed) && acceptingCrosses && avgDistance > 3){ 
      crossedLines++;
      acceptingCrosses = 0;
      startDistance = avgDistance;
    }
    if(avgDistance >= (startDistance + 3)) acceptingCrosses = 1;
    
    avgDistance = leftMotor->getDistance()/2+rightMotor->getDistance()/2;
    if(crossedLines > allowedCrosses){
      drivingForward = 0;
      return 1;
    }
  }
  if(!drivingForward || avgDistance>=target) {
    leftMotor->drive(0);
    rightMotor->drive(0);
    if(DEBUG)Serial.println("Forward move finished!");
    drivingForward = 0;
    return 1;
  }
  return 0;
}

uint8_t Move::to(uint8_t target, int16_t speed){
  if(target == currentPosition) return 1;
  
//  //we will always want to backout and turn around
//  forward(20,-speed, 1); 
//  turn(speed, 180);
//  uint8_t moves;
//  
//  if(currentPosition[0] == targetX) moves = 1; //on the long line
//  else if(currentPosition[1] == targetY) moves = 1; //going across field
//  else if(targetX == 0) moves = 2;  //going to the center 
//  else if(currentPosition[0] == 0) moves = 2; //in the center going elsewhere
//  else moves = 3;
//  
//  if(DEBUG){
//    Serial.print("Making ");
//    Serial.print(moves);
//    Serial.println(" moves");
//  }
//  if(moves == 1){
//    if(currentPosition[0] == targetX)forward(FIELD_Y, speed, 4);
//    else if(currentPosition[1] == targetY)forward(FIELD_X, speed, 1);
//  }
//  else if(moves == 2){
//    
//    
//  }
//  else if(moves == 3){
//    
//    
//    
//  }
  return 0;
}

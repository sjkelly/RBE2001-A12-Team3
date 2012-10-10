#include "move.h"

Move::Move(uint8_t _bumperPin, LineSensor* _lineSensor, Motor* _leftMotor, Motor* _rightMotor)
{
  pinMode(_bumperPin, INPUT);
  digitalWrite(_bumperPin, HIGH);       // turn on pullup resistors for our switch
  bumperPin = _bumperPin;
  currentPosition = SPENT_2;
  lineSensor = _lineSensor;
  leftMotor = _leftMotor;
  rightMotor = _rightMotor;
  turning = 0;
  drivingForward = 0; 
  moving = 0;
  position.x = START_X; //set the former destination to the starting place on the field.
  position.y = START_Y;
  heading = EAST; 
}

uint8_t Move::followLine(int16_t speed)
{
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
 else if(lineSensor->frontLeft){
  leftMotor->drive(0);
  rightMotor->drive(speed);   
   
 }
 else if(lineSensor->frontRight){
  leftMotor->drive(speed);
  rightMotor->drive(0);   
   
 }
 }
 return 0;
}

uint8_t Move::checkBumper(void){
  return !digitalRead(bumperPin);
}

uint8_t Move::turn(int16_t angle, int16_t speed){
 //lineSensor->update();
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
   if (angle%90 == 0 && lineSensor->rearRight && lineSensor->rearLeft && lineSensor->consecutiveStates >= LINE_SENSOR_CONSECUTIVE_READS && 
       leftMotor->getDistance() >= turnTarget - 2 && rightMotor->getDistance() > turnTarget - 2){
     rightMotor->drive(0);  
     leftMotor->drive(0); 
     if(DEBUG)Serial.println("Turn finished!");
     turning = 0;
     turnTarget = 0;
     return 1;
   }
   return 0;
 }
 else {
   rightMotor->drive(0);  
   leftMotor->drive(0); 
   if(DEBUG)Serial.println("Turn finished!");
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
      crossedLines = 0;
      drivingForward = 0;
      leftMotor->drive(0);
      rightMotor->drive(0);   
      if(DEBUG)Serial.println("Forward move finished!");
      return 1;
    }
  }
  if(!drivingForward || avgDistance>=target || checkBumper()) {
    leftMotor->drive(0);
    rightMotor->drive(0);
    if(DEBUG)Serial.println("Forward move finished!");
    crossedLines = 0;
    drivingForward = 0;
    return 1;
  }
  return 0;
}
uint8_t Move::matchDirection(direction _heading)
{
 int16_t angle = ((90*(heading - _heading))%180);
 return turn(angle, DEFSPEED);
}

uint8_t Move::to(uint8_t target, int16_t speed)
{
 coord destcoord;
 switch (target)
 {
  case REACTOR_A:
   destcoord.x = 1;
   destcoord.y = 3;
   break;
  case REACTOR_B:
   destcoord.x = 8;
   destcoord.y = 3;
   break;
  case SPENT_1:
   destcoord.x = 3;
   destcoord.y = 1;
   break;
  case SPENT_2:
   destcoord.x = 4;
   destcoord.y = 1;
   break;
  case SPENT_3:
   destcoord.x = 5;
   destcoord.y = 1;
   break;
  case SPENT_4:
   destcoord.x = 6;
   destcoord.y = 1;
   break;
  case NEW_1:
   destcoord.x = 3;
   destcoord.y = 5;
   break;
  case NEW_2:
   destcoord.x = 4;
   destcoord.y = 5;
   break;
  case NEW_3:
   destcoord.x = 5;
   destcoord.y = 5;
   break;
  case NEW_4:
   destcoord.x = 6;
   destcoord.y = 5;
 }
 coord relative;  //here we figure out where we are relative to where we have to go
 relative.x = destcoord.x = position.x;
 relative.y = destcoord.y = position.y;
 if(relative.x == 0 && relative.y == 0) //if we are where we need to go, set the positon to our destinaton, and return a sucessful move
 { 
  position.x = destcoord.x;	 
  position.y = destcoord.y;
  return 1;
 }
 //this is where it checks the relative position in order to figure out what it has to do. It is a little redundant becuase it has to onnly move horizontally if
 //it is in the middle column
 switch (relative.y)
 {
  case 4:   //if we have to move vertically across the entire field we have to back out
  case -4:
   if(forward(25, -DEFSPEED, 3))  //back out
    position.y += (relative.y > 0)?-1:1; //increment the position, also think about setting direction here
   break;
  case 3: //if we have backed out, we need to start traversing the field
  case -3:
   if(matchDirection((relative.y > 0)?NORTH:SOUTH)) //turn to the correct direction
   {
    if(forward(HEIGHT_DISTANCE, DEFSPEED, 1)) //once we have matched the direction, start actually moving down the field by line following
    {
     position.y += (relative.y > 0)?-1:1; //once we have finished moving, update our position by an increment
    }
   } 
  case 0: //this means we are going to a reactor tube
   if(abs(relative.x) == 1) //if we are only one away, we need to align to the reactor tube
   {
     if(forward(100, DEFSPEED, 3)) //this will ensure that the move forward is only tripped by the front bumper
      position.y += (relative.y > 0)?-1:1; //when it is tripped, we need to update our position, also think about setting direction here
   }
  case 2:
  case -2:
   if(position.x == 1 || position.x == 8) //if we are already at a reactor, we need to back out or we are at a tube and we need to back out
   {
     if(forward(25, -DEFSPEED, 3)) //back out
       {
        position.x += (relative.x > 0)?-1:1; //update our position by an increment, also think about setting direction here
       }
     
   }
   else if(relative.x !=0)  //if we are not at the coordinate we want to be at, we need to get there
   { 
    if(matchDirection((relative.x > 0)?EAST:WEST)) //turn to the direction we need to be facing
    {  
      if(forward(500, DEFSPEED, relative.x )) //then we actually need to move to the correct position
      {
       position.x = (relative.y != 0)?0:(relative.x > 0)?1:-1; //and finally increment our position when we have completed the move
      }
    }
   }
   else if(relative.y != 0); //finally, now that we are at the x coordinate that we want, we have to move across the field verticallly 
   {
    if(matchDirection((relative.y > 0)?NORTH:SOUTH)) // face the right direction
    {
     if(forward(HEIGHT_DISTANCE, DEFSPEED, 1)) //move across the y field
     {
      position.y += (relative.y > 0)?-1:1; //and increment our position on a sucessful move
     }
    }
   }
   break;
  case 1: //we are one vertical move away from moving across the field
  case -1:
    if(forward(100, DEFSPEED, 3)) //move vertically for the last time
      position.y += (relative.y > 0)?-1:1; //also think about setting direction here
   break;
  }
 return 0;
}
/*{
  if(!moving){
    if(target == currentPosition) return 1; //at the position already. we are done
    executedMoves = 0;
    //find # of moves
    if((target + 1 == REACTOR_B || target-1 == REACTOR_A) && (currentPosition == REACTOR_A || currentPosition == REACTOR_B)) moves = 1;
    else if((currentPosition+4 == target || currentPosition-4 == target) && (currentPosition > REACTOR_B)) moves = 1;
    else if(target > REACTOR_B && currentPosition <= REACTOR_B) moves = 2;
    else if(target <= REACTOR_B && currentPosition > REACTOR_B) moves = 2;
    else moves = 3;
    
    //find allowable crosses
    if(moves == 1 && target == REACTOR_B){ moveCrosses = 4; forwardLength = FIELD_Y; }
    else if(moves == 1 && target > REACTOR_B) { moveCrosses = 1; forwardLength = FIELD_X;}
    else if(moves == 2 && currentPosition <= REACTOR_B) {
      //calculate turn direction
      if(currentPosition == REACTOR_A && target <= NEW_4){
        moveCrosses = target - 2;
        turnFirst = 90;
      }
      else if(currentPosition == REACTOR_A && target > NEW_4){
        moveCrosses = target - 6;
        turnFirst = -90;
      }
      else if(currentPosition == REACTOR_B && target <= NEW_4){
        moveCrosses = 5 - target;
        turnFirst = -90;
      }
      else if(currentPosition == REACTOR_B && target > NEW_4){
        moveCrosses = 9 - target;
        turnFirst = 90;
      }
    }
    else if(moves == 2 && currentPosition > REACTOR_B) {
      //calculate turn direction
      if(currentPosition < NEW_4 && target == REACTOR_A){
        moveCrosses = currentPosition - 2;
        turnFirst = -90;
      }
      else if(currentPosition >= NEW_4 && target == REACTOR_A){
        moveCrosses = currentPosition - 6;
        turnFirst = -90;
      }
      if(currentPosition < SPENT_1 && target == REACTOR_B){
        moveCrosses = currentPosition - 2;
        turnFirst = 90;
      }
      else if(currentPosition >= SPENT_1 && target == REACTOR_B){
        moveCrosses = currentPosition - 9;
        turnFirst = 90;
      }
    }
    else if(moves == 3) {
      moveCrosses = abs(currentPosition - target + 4);
      if(currentPosition <= NEW_4 && currentPosition + 4 > target) turnFirst = -90;
      if(currentPosition <= NEW_4 && currentPosition + 4 < target) turnFirst = 90;
      if(currentPosition > NEW_4 && currentPosition - 4 > target) turnFirst = -90;
      if(currentPosition > NEW_4 && currentPosition - 4 < target) turnFirst = 90;
    } 
    moving = 1;
    forwardLength = FIELD_Y;
    if(DEBUG){
      Serial.print("Move values > ");
      Serial.print(" turnFirst:");
      Serial.print(turnFirst);
      Serial.print(" moveCrosses:");
      Serial.print(moveCrosses);
      Serial.print(" forwardLength:");
      Serial.println(forwardLength);
    }
  }
  if(moving){
    if(moves == 1){
      if(executedMoves == 0) executedMoves += forward(20,-speed, 1); //reverse 20
      if(executedMoves == 1) executedMoves += turn(speed, 180); 
      if(executedMoves == 2) executedMoves += forward(forwardLength,speed, moveCrosses);
      if(executedMoves == 3){ moving = 0; currentPosition = target; }
    }
    else if(moves == 2){
      if(executedMoves == 0) executedMoves += forward(20,-speed, 1); 
      if(executedMoves == 1) executedMoves += turn(180, speed);
      if(executedMoves == 2) executedMoves += forward(FIELD_Y,speed, 0);
      if(executedMoves == 3) executedMoves += turn(turnFirst, speed);
      if(executedMoves == 4) executedMoves += forward(forwardLength, speed, moveCrosses);      
      if(executedMoves == 5){ moving = 0; currentPosition = target; }
    }
    else if(moves == 3){ //moves == 3
      if(executedMoves == 0) executedMoves += forward(20,-speed, 1); 
      if(executedMoves == 1) executedMoves += turn(180, speed);
      if(executedMoves == 2) executedMoves += forward(FIELD_X/2,speed, 0);
      if(executedMoves == 3) executedMoves += turn(turnFirst, speed);
      if(executedMoves == 4) executedMoves += forward(forwardLength, speed, moveCrosses);
      if(executedMoves == 5) executedMoves += turn(turnFirst*-1, speed);
      if(executedMoves == 6) executedMoves += forward(FIELD_X/2,speed, 0);      
      if(executedMoves == 7){ moving = 0; currentPosition = target; }
    }
  }
  if(!moving){
   leftMotor->drive(0); 
   rightMotor->drive(0);
   return 1;
  }
  return 0;
}*///this is the defunct move to

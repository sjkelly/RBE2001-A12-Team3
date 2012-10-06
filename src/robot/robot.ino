#include <MsTimer2.h>
#include "robot.h"
#include "bluetooth.h"
#include "linesensor.h"
#include "move.h"
#include "motor.h"
#include "comms.h"

//Object Constructors
LineSensor lineSensor(LINE_SENSOR_CHARGE_US,LINE_SENSOR_READ_US);
Motor leftMotor(LEFT_ENCODER,LEFT_DRIVE,LEFT_1A,LEFT_2A);
Motor rightMotor(RIGHT_ENCODER,RIGHT_DRIVE,RIGHT_1A,RIGHT_2A);
Move move(BUMPER_PIN, &lineSensor, &leftMotor, &rightMotor);
btInterface mainBluetooth;

int i =0;
volatile bool beatFlag = 0;

void setup(){
  
  Serial.begin(9600);
  MsTimer2::set(1000, beat);
  attachInterrupt(leftMotor.interruptPin,leftEncoderISR,CHANGE);
  attachInterrupt(rightMotor.interruptPin,rightEncoderISR,CHANGE);
  MsTimer2::start();
}


void loop(){

  if(beatFlag)
  {
    mainBluetooth.sendHeartbeat();
    if(DEBUG)Serial.println("Timer Tick!");
    beatFlag = 0;
  }
  if(DEBUG) debug(&lineSensor, &leftMotor, &rightMotor, &move);
  /*
  lineSensor.update();
 
  if(!i){
    //move.to(0, FIELD_Y, 200);
    //move.forward(30, 200, 255);
    i++;
  }

  ///*
  if(move.checkBumper())move.followLine(125);
  else{
    leftMotor.drive(0);
    rightMotor.drive(0);
  }
  */
}


/*** ISRs ***/
//Cannot be class methods!

void rightEncoderISR(){
  rightMotor.count+=2; 
}

void leftEncoderISR(){
  leftMotor.count+=2;
}

void heartBeat()
{
  beatFlag = 1;
}



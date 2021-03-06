#include <MsTimer2.h>
#include "robot.h"

#include "linesensor.h"
#include "move.h"
#include "motor.h"
#include "comms.h"
#include "bluetooth.h"





//Object Constructors
fieldState actualField;

LineSensor lineSensor(LINE_SENSOR_CHARGE_US,LINE_SENSOR_READ_US);
Motor leftMotor(LEFT_ENCODER,LEFT_DRIVE,LEFT_1A,LEFT_2A);
Motor rightMotor(RIGHT_ENCODER,RIGHT_DRIVE,RIGHT_1A,RIGHT_2A);
Move move(BUMPER_PIN, &lineSensor, &leftMotor, &rightMotor);
int i =0;
decisionEng theDecider(&actualField);
btInterface mainBluetooth(&theDecider);
volatile bool beatFlag = 0;

void setup(){
  
  Serial.begin(9600);
  MsTimer2::set(1000, heartBeat);
  attachInterrupt(leftMotor.interruptPin,leftEncoderISR,CHANGE);
  attachInterrupt(rightMotor.interruptPin,rightEncoderISR,CHANGE);
  MsTimer2::start();
}


void loop(){
  if(mainBluetooth.btRecieve())
  {
    mainBluetooth.btHandle();
  }
  if(beatFlag)
  {
    mainBluetooth.sendHeartbeat();
    if(DEBUG)Serial.println("Timer Tick!");
    beatFlag = 0;
  }
  if(DEBUG) debug(&lineSensor, &leftMotor, &rightMotor, &move);


//move.forward(150, 200, 0);
  if(i == 0) i += move.forward(150, 250, 0);
 
  if(i == 1) i += move.turn(180, 200);

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



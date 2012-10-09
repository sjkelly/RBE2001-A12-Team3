#include <MsTimer2.h>
//#include <Servo.h>
#include "robot.h"

#include "linesensor.h"
#include "move.h"
#include "motor.h"
#include "comms.h"
#include "bluetooth.h"
#include "actuation.h"

void resetField(fieldState *_fieldstate);


//Object Constructors
fieldState actualField;
uint8_t destination;
LineSensor lineSensor(LINE_SENSOR_CHARGE_US,LINE_SENSOR_READ_US);
Motor leftMotor(LEFT_ENCODER,LEFT_DRIVE,LEFT_1A,LEFT_2A);
Motor rightMotor(RIGHT_ENCODER,RIGHT_DRIVE,RIGHT_1A,RIGHT_2A);
Move move(BUMPER_PIN, &lineSensor, &leftMotor, &rightMotor);
Servo clawServo, wristServo, liftServo;
Actuation mainActuation(&clawServo, &wristServo, &liftServo, TOP_BUMPER, BOT_BUMPER);
int i = 0;
decisionEng theDecider(&actualField);
btInterface mainBluetooth(&theDecider);
volatile bool beatFlag = 0;

void setup(){
  
  Serial.begin(9600);
  MsTimer2::set(1000, heartBeat);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  attachInterrupt(leftMotor.interruptPin,leftEncoderISR,CHANGE);
  attachInterrupt(rightMotor.interruptPin,rightEncoderISR,CHANGE);
  attachInterrupt(TOP_BUMPER, _reachUp, FALLING);
  attachInterrupt(BOT_BUMPER, _reachDown, FALLING);
  clawServo.attach(CLAW_SERVO);
  wristServo.attach(WRIST_SERVO);
  liftServo.attach(LIFT_SERVO);
  MsTimer2::start();
  resetField(&actualField);
  destination = theDecider.determineDest();
  mainActuation.moveUp();
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
  if(move.to(destination, DEFSPEED))
  {
   switch(destination)
   {
    case REACTOR_A:
    case REACTOR_B:
     if((destination == REACTOR_A)?actualField.reactorA:actualField.reactorB == SPENT_ROD)
     {
       mainActuation.closeClaw();
      if(mainActuation.moveUp())//insert actuation code here, check for successful completion
      {
       actualField.clawContents = SPENT_ROD;
       (destination == REACTOR_A)?actualField.reactorA:actualField.reactorB = NO_ROD;
       destination = theDecider.determineDest();
      }
    }
     else
     {
      if(mainActuation.moveDown())//inserto actuation code, check for sucessful complettion
      {
        mainActuation.openClaw();
       (destination == REACTOR_A)?actualField.reactorA:actualField.reactorB = NEW_ROD;
       destination = theDecider.determineDest();
       actualField.clawContents = NO_ROD;
      }
     }
     break;
    case SPENT_1:
    case SPENT_2:
    case SPENT_3:
    case SPENT_4:
     mainActuation.openClaw();   
     actualField.clawContents = NO_ROD;
     destination = theDecider.determineDest();
     break;
    case NEW_1:
    case NEW_2:
    case NEW_3:
    case NEW_4:
     mainActuation.closeClaw();
     actualField.clawContents = NEW_ROD;
     destination = theDecider.determineDest();
     
   }
  }
  else
  {
    switch(destination)
    {
     case NEW_1:
     case NEW_2:
     case NEW_3:
     case NEW_4:
     case SPENT_1:
     case SPENT_2:
     case SPENT_3:
     case SPENT_4:
      mainActuation.moveUp();
      break;
     case REACTOR_A:
     case REACTOR_B:
      if(actualField.clawContents == NO_ROD)
       mainActuation.moveDown();
      
     
    }
  }
  mainActuation.updateClaw();
//move.forward(150, 200, 0);
  // if(i == 0) i += move.forward(150, 250, 0);
  // if(i == 1) i += move.turn(90, 200);
   if(i == 0) i+= move.to(NEW_1,200);
  //if(i == 1) i += move.turn(180, 200);
}
//A helper that resets the field state
void resetField(fieldState *_fieldstate)
{
 _fieldstate->clawContents = NO_ROD;
 _fieldstate->reactorA = SPENT_ROD;
 _fieldstate->reactorB = SPENT_ROD;
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

void _reachUp()
{
  mainActuation.upReach();
}
void _reachDown()
{
  mainActuation.downReach();
}


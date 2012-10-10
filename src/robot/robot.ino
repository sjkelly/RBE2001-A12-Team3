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
uint8_t destination = REACTOR_A;
uint8_t blinkflag;
LineSensor lineSensor(LINE_SENSOR_CHARGE_US,LINE_SENSOR_READ_US);
Motor leftMotor(LEFT_ENCODER,LEFT_DRIVE,LEFT_1A,LEFT_2A,LEFT_PROPORTION);
Motor rightMotor(RIGHT_ENCODER,RIGHT_DRIVE,RIGHT_1A,RIGHT_2A,RIGHT_PROPORTION);
Move move(BUMPER_PIN, &lineSensor, &leftMotor, &rightMotor);
Servo clawServo, wristServo, liftServo;
Actuation mainActuation(&clawServo, &wristServo, &liftServo, TOP_BUMPER, BOT_BUMPER);
int i = 0, startUp = 1, startSequence = 0;
decisionEng theDecider(&actualField);
btInterface mainBluetooth(&theDecider);
volatile bool beatFlag = 0;

void setup(){
  
  Serial.begin(9600);
  MsTimer2::set(1000, heartBeat);
  //limit switches111
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  //blink LEDs
  pinMode(30, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(30, LOW);
  digitalWrite(33, LOW);
  //Attaching all of our interrupts
  attachInterrupt(leftMotor.interruptPin,leftEncoderISR,CHANGE);
  attachInterrupt(rightMotor.interruptPin,rightEncoderISR,CHANGE);
  attachInterrupt(TOP_BUMPER, _reachUp, FALLING);
  attachInterrupt(BOT_BUMPER, _reachDown, FALLING);
  /*
  attachInterrupt(TOP_BUMPER, _reachMid, RISING);
  attachInterrupt(BOT_BUMPER, _reachMid, RISING);
  */
  clawServo.attach(CLAW_SERVO);
  wristServo.attach(WRIST_SERVO);
  liftServo.attach(LIFT_SERVO);
  MsTimer2::start();
  resetField(&actualField);
  destination = theDecider.determineDest();
  mainActuation.moveUp();
}



void loop(){
  lineSensor.update();
  if(mainBluetooth.btRecieve())
  {
    mainBluetooth.btHandle();
  }
  if(beatFlag)
  {
    blinkflag = !blinkflag;
    mainBluetooth.sendHeartbeat();
    if(actualField.clawContents == NEW_ROD)
    {
     mainBluetooth.sendNewRadiation();
     digitalWrite(30, blinkflag);
     digitalWrite(30, blinkflag);
    }
    else if(actualField.clawContents == SPENT_ROD)
    {
      mainBluetooth.sendSpentRadiation();
      digitalWrite(30, blinkflag);
      digitalWrite(30, blinkflag);
    }
    else
    {
     digitalWrite(30, LOW);
     digitalWrite(30, LOW);
    }
    if(DEBUG)Serial.println("Timer Tick!");
    beatFlag = 0;
  }
  if(DEBUG) debug(&lineSensor, &leftMotor, &rightMotor, &move);
  

  //startup sequence to get us to the reactor at the start
  if(startUp){
    switch(startSequence)
    {
    case 0:
      startSequence += move.forward(50,DEFSPEED, 0); 
      break;  
    case 1:
      startSequence += move.turn(90, DEFSPEED); 
      break;
    case 2:
      startSequence += move.forward(50,DEFSPEED, 0); 
      break;
    case 3:
      startSequence += move.turn(90,DEFSPEED); 
      break;
    case 4:
      startSequence += move.forward(70,DEFSPEED, 1);
      break;
    case 5: 
      startUp = 0;
      break; 
    }
  }
  else if(!startUp && move.to(destination, DEFSPEED)) //check if an action has completed
  {
   switch(destination) //what we should do is determined by where we have just arrived
   {
    case REACTOR_A: //if we are at a reactor
    case REACTOR_B:
     if((destination == REACTOR_A)?actualField.reactorA:actualField.reactorB == SPENT_ROD) //if there is a spent rod in the reactor tube
     {
      if(mainActuation.moveDown())//on successful move, move down in order to get rod
      {
       mainActuation.closeClaw();//close claw, grab rod
       actualField.clawContents = SPENT_ROD; //robot is holding a spent rod
       (destination == REACTOR_A)?actualField.reactorA:actualField.reactorB = NO_ROD; //no more rod in the reactor
       destination = theDecider.determineDest(); //go to a new place
      }
      else //if still moving down, make sure that the claw is open to grab rod
      {
        mainActuation.openClaw();
      }
     }
     else //if there is no rod in there
     {
      if(mainActuation.moveDown())//move down to insert the rod in
      {
        mainActuation.openClaw(); //open the claw, drop rod in
       actualField.clawContents = NO_ROD; //we are no longer holding a rod
       (destination == REACTOR_A)?actualField.reactorA:actualField.reactorB = NEW_ROD; //there is now a new rod in the reactor
       destination = theDecider.determineDest(); //go to a new place

      }
     }
     break;
    case SPENT_1:   //if we are at a storage tube
    case SPENT_2:
    case SPENT_3:
    case SPENT_4:
     mainActuation.openClaw();//open the claw to drop spent rod in   
     actualField.clawContents = NO_ROD; //we are no longer holding a rod
     destination = theDecider.determineDest(); //go somewhere else
     break;
    case NEW_1: //if we are at a supply tube
    case NEW_2:
    case NEW_3:
    case NEW_4:
     mainActuation.closeClaw(); //close claw to grab new rod
     actualField.clawContents = NEW_ROD; //we are now holding a new rod
     destination = theDecider.determineDest(); // go somewhere else
     
   }
  }
  else //if we are currently in the middle of moving somewhere
  {
    if(actualField.clawContents == NO_ROD) //if we are not holding a rod, the claw should be open
     mainActuation.openClaw();
    else
    {
     mainActuation.closeClaw(); //if we are holding a rod, the claw should be closed so we don't drop it
     
     mainActuation.moveUp(); //no matter where we are going, our claw should be up
    }
  }
  mainActuation.updateClaw();
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
/*
void _reachMid()
{
  main.Actuation.midReach();
}*/


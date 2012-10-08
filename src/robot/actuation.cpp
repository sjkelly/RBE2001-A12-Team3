#include <Servo.h>
#include <Arduino.h>
 

// ROBS ELEVATOR
// by ROB



//////////////////////////////////////////
//////////////     STATES   //////////////
//////////////////////////////////////////

// master states
#define TAKE_FROM_REACTOR     0
#define GIVE_TO_TUBE          1

#define TAKE_FROM_TUBE        2
#define GIVE_TO_REACTOR       3


// action states
#define INITIALIZE      10  // some stuff
#define INITIALIZED     11
#define INVERT_GRIP     12
#define INVERT_ELEVATOR 13
#define INVERT_WRIST    14

// elevator states
#define TOP           1   // elevator is at the top
#define BOTTOM        0   // elevator is at the bottom
#define SOMEWHERE     2

// gripper states
#define GRIPPER_IS_OPEN   0
#define GRIPPER_IS_CLOSED 1
#define SOMEWHERE         2

// wrist states
#define WRIST_IS_DOWN        0 
#define WRIST_IS_OUT         1
#define SOMEWHERE            2
//////////////////////////////////////////
////////  SERVO  COMMANDS   //////////////
//////////////////////////////////////////

#define UP            50   // up elevator
#define DOWN          130  // down elevator

#define GRIPPER_OPEN   32  // opens gripper
#define GRIPPER_CLOSED 155 //Close gripper

#define HORIZONTAL     12  // wrist/gripper is pointed down
#define VERTICAL      118 // wrist/gripper is pointed out

//////////////////////////////////////////
//////////   VARIABLES      //////////////
//////////////////////////////////////////
int masterState  = 0     ;
int masterFlag   = 0     ;
int actionState = INITIALIZE;  // current state

Servo elevatorServo;    // elevator motor
Servo gripperServo;     // gripper servo
Servo wristServo;       // gripper rotator servo
 
const int topLimitSwitch    =  3;     // the number of the pushbutton pin   // int # 1
const int bottomLimitSwitch =  2;                                           // int # 0

// ISR ints   and   state ques
volatile int changeState = 0;          // 0 indicates do not change state, 1 indicates the need for a state change
int changeAction         = 1;          // set to 1 so that the system initializes itself
int lastTime             = 0;          // records the last time that something was done

volatile int elevatorPosition = SOMEWHERE;    // 2 = somewhere in the middle, TOP    BOTTOM
int gripperPosition            = SOMEWHERE;    // 2 = somewhere ,GRIPPER_IS_OPEN    GRIPPER_IS_CLOSED        ALSO INDICATES WHETHER OR NOT WE ARE HOLDING SOMETHING
int wristPosition             = SOMEWHERE;    // 2 = somewhere , WRIST_OUT    or WRIST_DOWN


//////////////////////////////////////////
////////////// INTERRUPTS   //////////////
//////////////////////////////////////////

void youHitTheTop ()
{
  elevatorPosition = TOP;    // sets this variable to say the elevator is at the top
  changeState = 1;           // indicates that the next state needs to happen in the loop
}

void youHitTheBottom()
{
  elevatorPosition = BOTTOM;    // sets this variable to say the elevator is at the bottom
  changeState = 1;             // indicates that the next state needs to happen in the loop
}
 

//////////////////////////////////////////
///////   STATE DECISIONS   //////////////
//////////////////////////////////////////
void decideElevatorAction ()
{
    if (INVERT_ELEVATOR == actionState && (elevatorPosition == TOP  ||  elevatorPosition == BOTTOM))  // if the elevator is at the top or bottom, we need it to stop
    {
        elevatorServo.write(90);   // stop the elevator because we are at a position
    }
  
    if (masterState == TAKE_FROM_REACTOR)    decideTakeFromReactor ();  
//    else if (masterState == GIVE_TO_TUBE)    decideGiveToTube ();   
//    else if (masterState == TAKE_FROM_TUBE)    decideTakeFromTube ();           
//    else if (masterState == GIVE_TO_REACTOR)    decideGiveToReactor ();           

  changeState  = 0 ;   // we have updated our state
  changeAction = 1 ;
}

void decideTakeFromReactor ()
{
    if (masterFlag == 0)                 // STAGE ZERO    INITIALIZE
    {
        if (elevatorPosition != TOP)   
             {
               elevatorServo.write(UP);
               elevatorPosition = SOMEWHERE;
             }
        else if (gripperPosition == GRIPPER_IS_CLOSED)  actionState = INVERT_GRIP;
        else if (wristPosition   == WRIST_IS_OUT)      actionState = INVERT_WRIST;
        else masterFlag ++;
    }
    else if (masterFlag == 1)            // STAGE ONE     DROP ELEVATOR
    {
        actionState = INVERT_ELEVATOR; 
        masterFlag ++;
    }  
    else if (masterFlag == 2 && elevatorPosition == BOTTOM)   // STAGE TWO   GRAB AND RAISE
    {
        if (gripperPosition == GRIPPER_IS_OPEN)  actionState = INVERT_GRIP;
        else if (elevatorPosition != TOP)   
             {
               elevatorServo.write(UP);
               elevatorPosition = SOMEWHERE;
             }
        else if (wristPosition == WRIST_IS_OUT)      actionState = INVERT_WRIST;
        else masterFlag ++;
    }
    else if (masterFlag == 3)
    {
      masterFlag = 0;
      masterState = GIVE_TO_TUBE; 
    }
}

/*
void decideGiveToTube ()
{
  if (masterFlag == 0) 
  {

//*/


 
//////////////////////////////////////////
///////   STATE ACTIONS     //////////////
////////////////////////////////////////// 
void executeElevatorAction ()
{
  if (actionState == INITIALIZE)
  {
        gripperServo.write(GRIPPER_OPEN);
        gripperPosition = GRIPPER_IS_OPEN ; 
        
        wristServo.write(HORIZONTAL);
        wristPosition = WRIST_IS_OUT;
        
        wristServo.write(UP);
        elevatorPosition = SOMEWHERE;
        masterState = TAKE_FROM_REACTOR;   ////// sets to first part of sequence
        Serial.println("initializing");
  }
  
  else if (actionState == INVERT_WRIST)
  {   
       if (wristPosition == WRIST_IS_DOWN)
       {
         wristServo.write(HORIZONTAL);
         wristPosition = WRIST_IS_OUT;
       }
       else if (wristPosition == WRIST_IS_OUT)
       {
         wristServo.write(VERTICAL);
         wristPosition = WRIST_IS_DOWN;
       }  
       Serial.println("inverting the wrist");  

}
  
  else if (actionState == INVERT_ELEVATOR)
  {
        if      (elevatorPosition == TOP)           elevatorServo.write(DOWN);        
        else if (elevatorPosition == BOTTOM)        elevatorServo.write(UP);
        Serial.println("inverting the elevator");       
  }
  
  else if (actionState == INVERT_GRIP)
  {
        gripperServo.write( !gripperPosition );
        gripperPosition = !gripperPosition;
        Serial.println("inverting the gripper"); 
  }
  actionState = 1;
  changeAction = 0;
  lastTime = millis();
}







 /*
void setup() 
{ 
  Serial.begin(9600);
  
  pinMode(topLimitSwitch, INPUT);     
  attachInterrupt (1, youHitTheTop, FALLING);
  
  pinMode(bottomLimitSwitch, INPUT);
  attachInterrupt (0, youHitTheBottom, FALLING);
    
  elevatorServo.attach(7,544,2400);  // attaches the servo on pin 9 to the servo object 
  gripperServo.attach(11,500,2000);   // write between 35 and 150
  wristServo.attach(12,500,2000);
} 
  


void loop() 
{    
  ////// STATE UPDATE TRIGGERS /////////
  if (changeState  >=1)              decideElevatorAction();
  if (changeAction >=1)              executeElevatorAction();
 
  if ((millis() - lastTime) >= 1500 && elevatorPosition != SOMEWHERE)   changeState = 1;    
} 
//*/

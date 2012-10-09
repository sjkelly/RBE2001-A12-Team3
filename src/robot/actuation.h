#ifndef ACTUATION_H
#define ACTUATION_H
#include "robot.h"
#include <stdint.h>
#include "Servo.h"

/** Values to send to Vex Motors**/
#define GOUP 50
#define GODOWN 130
#define FACEUP 127
#define FACEDOWN 15
#define STILL 90
#define OPEN 90
#define CLOSE 250

//Enumerated states for the position of the lift and claw
enum actLiftState {UP=1, DOWN=0};
enum actClawState {CLOSED=1, OPENED = 0};

class Actuation
{
 private:
  //variables for the positoin of the manipulator
  //the lift state gets determined by hardware interrupts coming from limit switches, so it is volatile
  volatile actLiftState currentLiftState;
  actClawState currentClaw, desiredClaw;
  //Servo objects to represent the motor and servos that move our manipulator
  Servo *clawServo;
  Servo *wristServo;
  Servo *liftServo;
  //the interrupt pins for our limit switches
  uint8_t topPin, botPin;
 public:
  Actuation(Servo*, Servo*, Servo*, uint8_t _topPin, uint8_t _botPin); 
  //Moves the Manipulator up and down
  //1 on already as high or low as can go
  uint8_t moveUp();
  uint8_t moveDown();
  //These two change hook into the interrupts triggered by the limit switches to track the position of the manipulator
  void downReach();
  void upReach();
  //closeClaw and openClaw only change the desired state of the claw, updateClaw is what actually changes it.
  void closeClaw();
  void openClaw();
  void updateClaw();
};

#endif

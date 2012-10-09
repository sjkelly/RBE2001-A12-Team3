#ifndef ACTUATION_H
#define ACTUATION_H
#include "robot.h"
#include <stdint.h>
#include "Servo.h"

#define GOUP 50
#define GODOWN 130
#define FACEUP 127
#define FACEDOWN 15
#define STILL 90
#define OPEN 90
#define CLOSE 250

enum actLiftState {UP=1, DOWN=0};
enum actClawState {CLOSED=1, OPENED = 0};
class Actuation
{
 private:
  volatile actLiftState currentLiftState;
  actClawState currentClaw, desiredClaw;
  Servo *clawServo;
  Servo *wristServo;
  Servo *liftServo;
  uint8_t topPin, botPin, clawPin, wristPin, liftPin;
 public:
  Actuation(Servo*, Servo*, Servo*, uint8_t _topPin, uint8_t _botPin); 
  //1 on already as high or low as can go
  uint8_t moveUp();
  uint8_t moveDown();
  void downReach();
  void upReach();
  void closeClaw();
  void openClaw();
  void updateClaw();
};

#endif

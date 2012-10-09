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
class Actuation
{
 private:
  actLiftState currentLiftState;
  uint8_t topPin, botPin;
  Servo *clawServo;
  Servo *wristServo;
  Servo *liftServo;
 public:
  Actuation(Servo*, Servo*, Servo*, uint8_t _topPin, uint8_t _botPin); 
  //1 on already as high or low as can go
  bool moveUp();
  bool moveDown();
  void downReach();
  void upReach();
  void closeClaw();
  void openClaw();
};

#endif

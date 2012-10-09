<<<<<<< HEAD

#define GOUP 50
#define GODOWN 130
#define FACEUP 127
#define FACEDOWN 15
#define STILL 90
=======
#define GOUP 0
#define GODOWN 0
#define FACEUP 0
#define FACEDOWN 0
#define STILL 0
>>>>>>> parent of a4c0e29... define values added to make sure actuation works
#define OPEN 90
#define CLOSE 250

#include "Arduino.h"
#include <Servo.h>
#include "robot.h"

#include <stdint.h>
enum actLiftState {UP=1, DOWN=0};
class Actuation
{
 private:
  actLiftState currentLiftState;
  uint8_t topPin, botPin;
  Servo clawServo, wristServo, liftServo;
 public:
  Actuation(uint8_t _clawPin, uint8_t _wristPin, uint8_t _liftPin, uint8_t _topPin, uint8_t _botPin); 
  //1 on already as high or low as can go
  bool moveUp();
  bool moveDown();
  void downReach();
  void upReach();
  void closeClaw();
  void openClaw();
};

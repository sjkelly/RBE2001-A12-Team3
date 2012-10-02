#include "robot.h"
#include "linesensor.h"
#include "move.h"
#include "motor.h"

LineSensor lineSensor;
Motor leftMotor(19,8,33,34,1);
Motor rightMotor(29,9,35,36,1);

void setup(){
  
  Serial.begin(9600);
  pinMode(BUMPER_PIN, INPUT);
  pinMode(LEFT_ENCODER, INPUT);
  pinMode(RIGHT_ENCODER, INPUT);
  
  digitalWrite(BUMPER_PIN, HIGH);       // turn on pullup resistors for our switch
  
  attachInterrupt(LEFT_ENCODER_INTERRUPT,leftEncoderISR,RISING);
  attachInterrupt(RIGHT_ENCODER_INTERRUPT,rightEncoderISR,RISING);
}

void loop(){
  if(DEBUG){
    lineSensor.print();
    Serial.print("Front Button State : ");
    Serial.println(Move::bumperHit);
    Serial.print("Motor Distances (cm) >");
    Serial.print(" Left : ");
    Serial.print(leftMotor.getDistance());
    Serial.print(" Right : ");
    Serial.println(rightMotor.getDistance());
  }
  lineSensor.update();
  
  if(Move::checkBumper())Move::followLine(125, lineSensor.frontLeft, lineSensor.frontRight, lineSensor.frontCenter, rightMotor, leftMotor);
  else{
    leftMotor.drive(0);
    rightMotor.drive(0);
  }
}

/*** ISRs **/

void rightEncoderISR(){
  rightMotor.count++; 
}

void leftEncoderISR(){
  leftMotor.count++;
}





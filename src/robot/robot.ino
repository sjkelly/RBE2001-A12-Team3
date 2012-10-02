#include "robot.h"
#include "linesensor.h"
#include "move.h"


lineSensor myLineSensor;
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
    myLineSensor.print();
    Serial.print("Front Button State : ");
    Serial.println(Move::bumperHit);
    Serial.print("Encoder Counts >");
    Serial.print(" Left : ");
    Serial.print(Move::leftCount);
    Serial.print(" Right : ");
    Serial.println(Move::rightCount);
  }
  myLineSensor.update();
  
  if(!digitalRead(BUMPER_PIN))Move::bumperHit = 1;
  else Move::bumperHit = 0;
  
  if(!Move::bumperHit)Move::followLine(125, myLineSensor.frontLeft, myLineSensor.frontRight, myLineSensor.frontCenter, rightMotor, leftMotor);
  else{
    leftMotor.drive(0);
    rightMotor.drive(0);
  }
}

void rightEncoderISR(){
  Move::rightCount++; 
}

void leftEncoderISR(){
  Move::leftCount++;
}





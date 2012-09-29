#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

lineSensor::lineSensor(){ 
}

void lineSensor::update(){
  
  DDRA = B00111111; //Set to output
  PORTA = B00111111; //write to output
  DDRA = B00000000; //set to input
  delayMicroseconds(CHARGE_MICROS); //Wait for a 
  
  uint32_t time = micros();
  
  while (micros() - time < READ_MICROS) state = PINA; 
  
  frontLeft = state & B00000001;
  frontRight = state & B00000010;
  frontCenter = state & B00000100;
  rearLeft = state & B00001000;
  rearRight = state & B00010000;
  rearCenter = state & B00100000;
  
}

void lineSensor::print(){
  Serial.print("Line Sensor States:");
  Serial.println(state,BIN);
}



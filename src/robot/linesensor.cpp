#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

LineSensor::LineSensor(uint16_t _charge, uint16_t _read){ 
  charge = _charge;
  read = _read;
}

void LineSensor::update(){
  noInterrupts();
  DDRA = B01111111; //Set to output
  PORTA = B01111111; //write to output
  delayMicroseconds(charge); //Wait for a 
  DDRA = B00000000; //set to input
  uint32_t time = micros();
  
  while (micros() - time < read) state = PINA; 
  
  if(state == lastState){
    consecutiveStates++;
    return;
  }
  else {
    consecutiveStates = 0;
    lastState = state;
    frontLeft = state & B00000001;
    frontRight = state & B00000010;
    frontCenter = state & B00000100;
    wingLeft = state & B00001000;
    wingRight = state & B00010000;
    rearRight = state & B00100000;
    rearLeft = state & B01000000;
  }
  interrupts();
}

/*#include "sensor.h"

void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
  DDRA = B00111111;
  //digitalWrite( QRE1113_Pin, HIGH );
  PORTA = B00111111;
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  DDRA = B00000000;
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS){
   if(!digitalRead(22)&&!sensor[0]) sensor[0] = 1; 
   if(!digitalRead(23)&&!sensor[1]) sensor[1] = 1; 
   if(!digitalRead(24)&&!sensor[2]) sensor[2] = 1; 
   if(!digitalRead(25)&&!sensor[3]) sensor[3] = 1; 
   if(!digitalRead(26)&&!sensor[4]) sensor[4] = 1; 
   if(!digitalRead(27)&&!sensor[5]) sensor[5] = 1; 
  }
}
void lineSensor::print(){
  int i;
  for(i=0; i<LINE_SENSOR_COUNT; i++){
    Serial.print(sensor[i]);
    sensor[i] = 0;
  }
}
*/


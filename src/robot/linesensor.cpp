#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

lineSensor::lineSensor(){ 
}

void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
   pinMode(22, OUTPUT);
   pinMode(23, OUTPUT);
   pinMode(24, OUTPUT);
   pinMode(25, OUTPUT);
   pinMode(26, OUTPUT);
   pinMode(27, OUTPUT);
   digitalWrite(22, HIGH);
   digitalWrite(23, HIGH);
   digitalWrite(24, HIGH);
   digitalWrite(25, HIGH);
   digitalWrite(26, HIGH);
   digitalWrite(27, HIGH);
  //digitalWrite( QRE1113_Pin, HIGH );
   pinMode(22, INPUT);
   pinMode(23, INPUT);
   pinMode(24, INPUT);
   pinMode(25, INPUT);
   pinMode(26, INPUT);
   pinMode(27, INPUT);
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS){
   if(!digitalRead(22)&&!sensor[0]) sensor[0] = micros() - time; 
   if(!digitalRead(23)&&!sensor[1]) sensor[1] = micros() - time; 
   if(!digitalRead(24)&&!sensor[2]) sensor[2] = micros() - time; 
   if(!digitalRead(25)&&!sensor[3]) sensor[3] = micros() - time; 
   if(!digitalRead(26)&&!sensor[4]) sensor[4] = micros() - time; 
   if(!digitalRead(27)&&!sensor[5]) sensor[5] = micros() - time; 
  }
}
void lineSensor::print(){
  int i;
  for(i=0; i<LINE_SENSOR_COUNT; i++){
    Serial.print(sensor[i]);
    Serial.print(' ');
    sensor[i] = 0;
  }
  Serial.print('\n');
}


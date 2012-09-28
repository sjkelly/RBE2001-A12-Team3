#include "linesensor.h"
#include "robot.h"

lineSensor::lineSensor(){ 
}

inline void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
  DDRD = B11111100;
  //digitalWrite( QRE1113_Pin, HIGH );
  PORTD = B11111100;
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  DDRD = B00000000;
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS){
   if(!digitalRead(LINE_SENSOR_FL)&&!frontLeft) frontLeft = 1; 
   if(!digitalRead(LINE_SENSOR_FC)&&!frontCenter) frontCenter = 1; 
   if(!digitalRead(LINE_SENSOR_FR)&&!frontRight) frontRight = 1; 
   if(!digitalRead(LINE_SENSOR_BL)&&!backLeft) backLeft = 1; 
   if(!digitalRead(LINE_SENSOR_BC)&&!backCenter) backCenter = 1; 
   if(!digitalRead(LINE_SENSOR_BR)&&!backRight) backRight = 1; 
  }
}
void lineSensor::print(){
	Serial.print("\tFL:");
  Serial.print(frontLeft);
	Serial.print("FC:");
	Serial.print(frontCenter);
	Serial.print("FR:");
	Serial.print(frontRight);
	Serial.print("BL:");
	Serial.print(backLeft);
	Serial.print("BC:");
	Serial.print(backCenter);
	Serial.print("BR:");
	Serial.print(backRight);
}

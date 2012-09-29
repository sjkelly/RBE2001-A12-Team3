#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

lineSensor::lineSensor(uint8_t _pin, uint16_t _threshold)
{ 
 pin = _pin;
 threshold = threshold; 
}

void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
   pinMode(pin, OUTPUT);
   digitalWrite(pin, HIGH);
  //digitalWrite( QRE1113_Pin, HIGH );
   pinMode(pin, INPUT);
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  uint32_t time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS)
  {
   if(!digitalRead(22)&&!value)
    value = micros() - time; 
  }
}
uint8_t lineSensor::getValue()
{
 return value;
}

bool lineSensor::seeLine()
{
 return value < threshold;
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


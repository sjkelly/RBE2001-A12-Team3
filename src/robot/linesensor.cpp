#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

lineSensor::lineSensor(uint8_t _pin, uint16_t _threshold);
{ 
 pin = _pin;
 threshold = threshold; 
}

static void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
  DDRA = B00111111;
  PORTA = B00111111;
  //digitalWrite( QRE1113_Pin, HIGH );
  DDRA = B0000000;
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  uint32_t time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS)
  {
   if(!digitalRead(pin)&&!state)
    value = micros() - time; 
  }
}
int lineSensor::getValue()
{
 return value;
}

bool lineSensor::seeLine()
{
 return value < threshold;
}

void lineSensor::print(){
  Serial.print(sensor[i]);
}


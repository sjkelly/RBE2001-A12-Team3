#include "linesensor.h"
#include "robot.h"
#include "Arduino.h"

lineSensor::lineSensor(uint8_t _pin, uint16_t _threshold)
{ 
 pin = _pin;
 threshold = threshold; 
 next = null;
 last->next = this;
 last = this;
}

//call immediately after a charge
uint16_t lineSensor::read()
{
  uint32_t time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS)
  {
   if(!digitalRead(pin)&&!value)
    return micros() - time; 
  }
}
static void lineSensor::updateAll()
{
 //charge all here with port assiment
 //LINE_PORT = CHARGE_VALUE;
 //these should both be defines
  lineSensor *i;
 for(i = this; i != NULL; i = i->next)
  {
   pinMode(i->getPin(), OUTPUT);
   digitalWrite(i->getPin(), HIGH);
   pinMode(i->getPin(), INPUT);
   }
 }
static void lineSensor::readAll()
{
 uitn32_t time = micros();
 while(micros - time < READ_MICROS)
 {
  lineSensor *i;
  for(i = this; i != NULL; i = i->next)
  {
   if(!digitalRead(i->getPin())&&!i->getValue())
    i->setValue(micros() - time);
  }
 }
}


void lineSensor::update()
{
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
  lineSensor::readAll();
}
uint8_t lineSensor::getValue()
{
 return value;
}

bool lineSensor::seeLine()
{
 return value < threshold;
}

void lineSensor::print()
{
    Serial.print(value);
    Serial.print(' ');
    Serial.print('\n');
}


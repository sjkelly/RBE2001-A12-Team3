/*Code for the QRE1113 Digital board
 *Outputs via the serial terminal - Lower numbers mean more reflected
 *3000 or more means nothing was reflected.
*/

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <avr/io.h>

#define LINE_SENSOR_COUNT 6 //don't change this really. you will break the member vars.
#define CHARGE_MICROS 10  //How long we charge the capacitor
#define READ_MICROS 1500 //How long we wait between 
#define MAX_SENSOR 8	//The maximum amount of line sensors

class lineSensor
{
  private:
   static uint8_t currentSensors;
   uint8_t pin;
   uint16_t value, threshold;
   lineSensor *next;
   static lineSensor *last;
  public:
   lineSensor(uint8_t pin, uint16_t _threshold);
   uint8_t getPin();
   static void updateAll();
   void update();
   uint16_t read();
   static void readAll();
   uint8_t getValue();
   uint8_t setValue();
   bool seeLine();
   void print();
};
#endif

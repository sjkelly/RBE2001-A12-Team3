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

class lineSensor{
  public:
  lineSensor();
  void update();
  void print();
  int sensor[LINE_SENSOR_COUNT];
  int frontLeft, frontRight, frontCenter, rearLeft, rearRight, rearCenter;
};
#endif

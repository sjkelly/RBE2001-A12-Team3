/*Code for the QRE1113 Digital board
 *Outputs via the serial terminal - Lower numbers mean more reflected
 *3000 or more means nothing was reflected.
*/

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <avr/io.h>
#include "robot.h"

class lineSensor{
  public:
  lineSensor();
  void update();
  void print();
  uint8_t state;
  uint8_t frontLeft, frontRight, frontCenter, rearLeft, rearRight, rearCenter;
};
#endif


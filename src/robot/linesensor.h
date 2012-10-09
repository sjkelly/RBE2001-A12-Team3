/*Code for the QRE1113 Digital board
 *Outputs via the serial terminal - Lower numbers mean more reflected
 *3000 or more means nothing was reflected.
*/

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <avr/io.h>
#include "robot.h"

class LineSensor{
  public:
  LineSensor(uint16_t,uint16_t);
  void update();
  uint8_t state, consecutiveStates;
  uint8_t frontLeft, frontRight, frontCenter, wingLeft, wingRight, rearRight, rearLeft;
  private:
  uint16_t charge, read;
  uint8_t lastState;
};
#endif


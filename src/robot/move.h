#ifndef __MOVEH__
#define __MOVEH__
#define HBRIDGE1 3
#define HBRIDGE2 4
#define ENABLE 5
#include "Arduino.h"
#include <stdlib.h>
enum direct {FORWARD, BACKWARD};
enum motor  {LEFT, RIGHT};


//namespace move
//{
driveMotor(int16_t speed, motor side);

  

#endif

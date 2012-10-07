#include "decision.h"

decisionEng::decisionEng(fieldState *_state)
{ 
 state = _state;
}
//both these functions are dependent on endianess, we will have to debug this
void decisionEng::supplyMessage(uint8_t _mask)
{
 Mask spMask;
 spMask.mask = _mask;
 int i = 0;
 state->new1 = spMask.bits[i];
 i++;
 state->new2 = spMask.bits[i];
 i++;
 state->new3 = spMask.bits[i];
 i++;
 state->new4 = spMask.bits[i];
}

void decisionEng::spentMessage(uint8_t _mask)
{
 Mask spMask;
 spMask.mask = _mask;
 int i = 0;
 state->spent1 = spMask.bits[i];
 i++;
 state->spent2 = spMask.bits[i];
 i++;
 state->spent3 = spMask.bits[i];
 i++;
 state->spent4 = spMask.bits[i];
 
}

uint8_t decisionEng::determineDest()
{
 switch (state->clawContents)
 {
  case NO_ROD:
   break;
  case SPENT_ROD:
   break;
  case NEW_ROD:
   break;
 }
}
//these are some uncommited changes


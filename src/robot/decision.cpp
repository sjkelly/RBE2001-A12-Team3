#include "decision.h"
//some helper functions
//tells the position of a leading bit in a mask
uint8_t leadingByte(Mask _mask)
{
  uint8_t i;
  for(i = 0;  i < 8; i++)
  {
    if(_mask.bitArray[i])
     return i;
  }
  return 0;
}

//tells us the positin of the last bit in a mask
uint8_t precedingByte(Mask _mask)
{
  uint8_t i;
  for(i = 8;  i > 0; i--)
  {
    if(_mask.bitArray[i-1])
     return i;
  }
  return 0;
}

decisionEng::decisionEng(fieldState *_state)
{ 
 state = _state;
}
//both these functions are dependent on endianess, we will have to debug this
void decisionEng::supplyMessage(uint8_t _mask)
{
 Mask spMask;
 spMask.Byte = _mask;
 int i = 0;
 state->storage.tubes.new1 = spMask.bitArray[i];
 i++;
 state->storage.tubes.new2 = spMask.bitArray[i];
 i++;
 state->storage.tubes.new3 = spMask.bitArray[i];
 i++;
 state->storage.tubes.new4 = spMask.bitArray[i];
}

void decisionEng::spentMessage(uint8_t _mask)
{
 Mask spMask;
 spMask.Byte = _mask;
 int i = 0;
 state->storage.tubes.spent1 = spMask.bitArray[i];
 i++;
 state->storage.tubes.spent2 = spMask.bitArray[i];
 i++;
 state->storage.tubes.spent3 = spMask.bitArray[i];
 i++;
 state->storage.tubes.spent4 = spMask.bitArray[i];
 
}

uint8_t decisionEng::determineDest()
{
 Mask spentStorageState;
 spentStorageState.Byte = state->storage.Byte & 0B11110000; 
 Mask newStorageState;
 newStorageState.Byte = state->storage.Byte & 0B00001111;
 switch (state->clawContents)
 {
  
  case SPENT_ROD:
   switch (leadingByte(spentStorageState))
   {
    case 1:
    //return spent storage 1
    break;
    case 2:
    //return spent storage 2
    break;
    case 3:
    //return spent storage 3
    break;
    case 4:
    //return spent storage 4
    break;
   } 
   break;
  case NEW_ROD:
   if(state->reactorA == NO_ROD){}
    //return reactor A
   else{}
    //return reactor B
   break;
  case NO_ROD:
   if ((state->reactorA == NO_ROD)||(state->reactorB == NO_ROD))
    switch (precedingByte(newStorageState))
    {
     case 1:
     //return new storage 1
     break;
     case 2:
     //return new storage 2
     break;
     case 3:
     //return new storage 3
     break;
     case 4:
     //return new storage 4
     break;
    }
   else if ((state->reactorA == SPENT_ROD)){}
    //return reactor A
   else if ((state->reactorB == SPENT_ROD)){}
    //return reactor B
   else{}
   //this last case will only occur when we have finished all of our actions
   //we can reset the field state here
 }
}
//these are some uncommited changes


  

#ifndef ___DECISION_____
#define ___DECISION_____
#include <stdint.h>
#include "robot.h"
/*** Enumeratoins ***/
//the enumeration for the contents of our claw and reactor tubes
enum tubeState {NO_ROD = 0x00, SPENT_ROD = 0x2C, NEW_ROD = 0xFF};
/*** Custom Structures ***/
union Mask
{
  uint8_t Byte;
  bool bitArray[7];
  struct{
  bool bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;
  }bits;
 //these are specifically here for the field state ussage of this
  struct{
  bool spent4, spent3, spent2, spent1, new1, new2, new3, new4;
  }tubes;
};

//this is a struct so that we can access it outside of the class
struct fieldState
{
 
 //1 for available, 2 for occupied
 Mask storage;
 //this represents the current content of our claw
 tubeState clawContents, reactorA, reactorB;
};


//This classes job is to decided where we go to next
class decisionEng
{
 private:
  //This is a pointer to a virtual representation of the field
  fieldState *state;
 public:
  decisionEng(fieldState *_state);
  //these two functions are called in order to allow the bluetooth class to provide the locations of open rod receptacles and new rods
  void supplyMessage(uint8_t _mask);
  void spentMessage(uint8_t _mask);
  
  //The actuall function that calculates where to go next
  uint8_t determineDest();
};

#endif

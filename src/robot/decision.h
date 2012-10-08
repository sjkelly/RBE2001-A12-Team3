#ifndef ___DECISION_____
#define ___DECISION_____
#include <stdint.h>

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

class decisionEng
{
 private:
  fieldState *state;
 public:
  decisionEng(fieldState *_state);
  void supplyMessage(uint8_t _mask);
  void spentMessage(uint8_t _mask);
  uint8_t determineDest();
  
  friend class btInterface;
};

#endif

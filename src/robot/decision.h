#include <stdint.h>
//enumeration for the contents of our claw
enum tubeState {NO_ROD = 0x00, SPENT_ROD = 0x2C, NEW_ROD = 0xFF};
//enum Action

union Mask
{
  uint8_t mask;
  bool bits[7];
};

//this is a struct so that we can access it outside of the class
struct fieldState
{
 //1 for available, 2 for occupied
 bool reactorA, spent4, spent3, spent2, spent1, reactorB, new1, new2, new3, new4;
 //this represents the current content of our claw
 tubeState clawContents; 
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
};

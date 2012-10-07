//enumeration for the contents of our claw
enum tubeState {NO_TUBE = 0x00, SPENT_ROD = 0x2C, NEW_ROD = 0xFF};

struct fieldState
{
 //1 for available, 2 for occupied
 bool reactorA, spent4, spent3, spent2, spent1, reactorB, new1, new2, new3, new4;
 //
 tubeState clawContents; 
}

class decisionEng
{
 private:
  fieldState *state;
 public:
  decisionEng(field State *_state);
  void supplyMessage(uint8_t mask);
  void spentMessage(uint8_t mask);
  uint8_t determineDest();
};

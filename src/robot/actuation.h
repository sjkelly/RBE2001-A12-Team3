enum actLiftState {UP=1, DOWN=0};
enum actClawState {OPEN=1, CLOSED=0};
class Actuation
{
 private:
  actState currentLiftState;
  uint8_t clawPin, wristPin, liftPin;
 public:
  Actuation(uint8_t _clawPin, uint8_t _wristPin, uint8_t _liftPin, uint8_t _topPin, uint8_t _botPin); 
  //1 on already as high or low as can go
  bool moveUP();
  bool moveDown();
  void downReach();
  void upReach();
  void closeClaw();
  void openClaw();
}

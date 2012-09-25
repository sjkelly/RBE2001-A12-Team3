#include "bluetooth.h"
btInterface::btInterface(int _btID)
{
 this->btID = _btID;
 Serial1.begin(115200); 
}
void btInterface::btRecieve(char *btByte = &btBuffer[0])
{
 while(Serial1.available()<0)
  {
   *btByte = Serial1.read();
   btByte++;
  }
} 

void btInterface.btHandle

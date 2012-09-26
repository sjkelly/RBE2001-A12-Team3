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

void btInterface.btHandle(char *btMessage = &btBuffer[0])
{
 swtich(*btBuffer[2])
 {
  //this is where we either hanld each bluetooth mesage or we create hooks into 
  //functions later in the proghram
  case:  
   STORAGE_TUBE:
   SUPPLY_TUBE:
   RADIATION_ALERT:
   STOP_MOVEMENT:
   RESUME_MOVEMENT:
   ROBOT_STATUS:
 }
}
//at this point, data needs a null character to terminate
void btInterface::btSend(btType type, char *data, char destination)
{
 char mBuffer[MAX_MESSAGE_SIZE];
 char *iterator = &mBuffer[4];
 //start delimiter
 mBuffer[0] = 0x5F;
 //message type
 mBuffer[2] = type;
 //source address
 mBuffer[3] = btID;
 //destination address
 mBuffer[4] = destination;
 int size;
 char checksum;
 //This is where the data is filled and the robot counts the size 
 for(size = 0; mBuffer[size] != '\0'; size++)
 {
  mBuffer[5+size] = data[size];
 }
 //size byte
 mBuffer[1] = size + 3;
 //just have to add checksum
}














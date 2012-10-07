#include "bluetooth.h"
//defines termianating character
//we should place this in a definitions file
//as well as change the terminating character to something the standard probably doesn't use
#define TERMINATOR '\0'
btInterface::btInterface(uint16_t _btID)
{
 this->btID = _btID;
 Serial1.begin(115200); 
}
void btInterface::btRecieve(uint8_t *btByte = &btBuffer[0])
{
 while(Serial1.available()<0)
  {
   *btByte = Serial1.read();
   btByte++;
  }
 *btByte = TERMINATOR;
} 

void btInterface::btHandle(uint8_t *btMessage = &btBuffer[0])
{
 //error checking, throws exception on error 
 if(btBuffer[0] != 0x5f)
  //debug wrong delimiter here
 uint16_t size;
 uint16_t checksum;
 for(size = 0; size+1 < btBuffer[1]; size++)
 {
  checksum += btMessage[size+2];
 }
 if(size != btMessage[2])
  //debug wrong size, possibly incomplete transmission
 if(btMessage[size] != (checksum < 0xff)?checksum:0xff)
  //debug worng checksum, possibly misread transimission
 swtich(btMessage[2])
 {
  //this is where we either hanld each bluetooth mesage or we create hooks into 
  //functions later in the proghram
  case STORAGE_TUBE:
  break;
  case SUPPLY_TUBE:
  break;
  case RADIATION_ALERT:
  break;
  case STOP_MOVEMENT:
  break;
  case RESUME_MOVEMENT:
  break;
 }
}
//at this point, data needs a null character to terminate
void btInterface::btSend(btType type, uint8_t *data, uint8_t destination)
{
 uint8_t mBuffer[MAX_MESSAGE_SIZE];
 uint8_t *iterator;
 //start delimiter
 mBuffer[0] = 0x5F;
 //message type
 mBuffer[2] = type;
 //source address
 mBuffer[3] = btID;
 //destination address
 mBuffer[4] = destination;
 uint16_t size;
 uint16_t checksum = type + btID + destination;
 //This is where the data is filled and the robot counts the size 
 for(size = 0; mBuffer[size] != TERMINATOR; size++)
 {
  mBuffer[5+size] = data[size];
 
  checksum += (uint16_t)data[size];
 }
 //size byte
 mBuffer[1] = size + 3;
 //checksum
 mBuffer[size + 5] = (checksum < 0xFF)?checksum:0xFF;
 mBuffer[size + 6] = TERMINATOR;
 for(iterator = &mBuffer[0]; *iterator != TERMINATOR; iterator++)
 {
  Serial1.print(*iterator);
 }
}


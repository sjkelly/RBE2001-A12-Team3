#include "bluetooth.h"
//defines termianating character
//we should place this in a definitions file
//as well as change the terminating character to something the standard probably doesn't use
#define TERMINATOR '\0'
btInterface::btInterface(decisionEng* _decider)
{
 this->btID = ID;
 decider = _decider;
 Serial3.begin(115200); 
}
bool btInterface::btRecieve(void)
{
 if(Serial3.available())
 {
 uint8_t *btByte = &btBuffer[0];
 while(Serial3.available()<0)
  {
   *btByte = Serial3.read();
   btByte++;
  }
  //*btByte = TERMINATOR;
 return 1;
 }
 return 0;
 
} 

void btInterface::btHandle()
{
  uint8_t *btMessage = &btBuffer[0];
 //error checking, throws exception on error 
 if(btBuffer[0] != 0x5f){}
  //debug wrong delimiter here
 uint16_t size;
 uint16_t checksum;
 for(size = 0; size+1 < btBuffer[1]; size++)
 {
  checksum += btMessage[size+2];
 }
 if(size != btMessage[2]){}
  //debug wrong size, possibly incomplete transmission
 if(btMessage[size+2] != (checksum < 0xff)?checksum:0xff){}
  //debug worng checksum, possibly misread transimission
 switch(btMessage[2])
 {
  //this is where we either hanld each bluetooth mesage or we create hooks into 
  //functions later in the proghram
  case STORAGE_TUBE:
  decider->state->storage.Byte = btMessage[3]<<4;
  if(DEBUG)
  {
    char dBuffer[20];
    sprintf(dBuffer, "Storage tube %d available", btMessage[3]);
    Serial.println(dBuffer);
  }  
  break;
  case SUPPLY_TUBE:
  decider->state->storage.Byte = btMessage[3];
  if(DEBUG)
  {
    char dBuffer[20];
    sprintf(dBuffer, "Storage tube %d available", btMessage[3]);
    Serial.println(dBuffer);
  }
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
void btInterface::btSend(btType type, uint8_t *data, uint8_t destination = 0x00)
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
 mBuffer[size + 6] = 0x0;
 for(iterator = &mBuffer[0]; *iterator != TERMINATOR; iterator++)
 {
  Serial3.print(*iterator);
 }
}

void btInterface::sendHeartbeat()
{
  //uint8_t data = 0x00;
  //btSend(HEARTBEAT, &data);
  
  uint8_t pkt[7] = {0x5F, 0x06, 0x07, 0x01, 0x00, 0x00, 0xF1};
  Serial3.write(pkt,7);
  
  //*/
} 



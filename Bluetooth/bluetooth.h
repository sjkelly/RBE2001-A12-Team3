#ifndef ___BLUETOOTH___
#define ___BLUETOOTH___

/*************
The purpose of this file is to provide an easy to use interface for sending and
recieving bluetooth messages from the master field coordinator. 

Goals:
-abstracted values: all numbers should be hidden from any code using this interface
-Endianess: because these values are being sent to us, and they use terms such as first and in the bluetooth doc, I'm going to treat the messages as big endian.

*******************/

//this is just a buffer enum, it doesn't belong here, but reprents any random buffers we want to hook into
//later
enum buffer



//the first step is going to be creating enums for the message types.
//we should also think about adding our own types of messages to this, because we can define our own 
//messages and communicate with the robot
enum btType {STORAGE_TUBE = 0x01, 
	    SUPPLY_TUBE = 0x02, 
	    RADIATION_ALERT = 0x04, 
	    STOP_MOVEMENT = 0x05, 
	    RESUME_MOVEMENT = 0x06, 
	    ROBOT_STATUS = 0x07};

//another enum for radiation levels
enum btRadiation {SPENT = 0x2C, 
		  NEW = 0xFF};


//and another enum for robot status
//this is so dumb that I'm not even going to attempt to come up with names for these, we'll figure it out later
//enum btRobotStatus 

//btID should represent our bluetooth id. I made it a variable so that it could be changed on runtime
int btID;

//this could be our buffer for storing bluetooth messages. We have to make sure we fill them as big
//endian. 300 is just a rounnd number that is above the maximum message size, and is a round number. 
//we should reduce this to gain some extra memory, it's kindof absurdly high right now.
char btBuffer[300];

//This is the Init function, it should be called during void setup()
//we should add an exeption to all of these in order to ensure that everyting initializes properly
initBluetooth();

//btHandle will handle the bluetooth message. It takes a pointer to a bluetooth message, and optionally 
//a pointer to a response buffer (right now It's just a buffer enum, howver it can represent something 
//like our action buffer) It should throw an exeption if something went wrong i.e. if the checksum doesn't 
//match the message, although if that happens frequently we should use a faster method of error checking
void btHandle(char *btMessage, *buffer aBuffer);

//btSend will be fore when the robot has to send out a message. it accepts a message type, and a pointer to
//the message data. I've also decided to include optional destination arguments, however we 
//should be able to tell what it should be based on the message type. once again, this should throw an 
//exception upon failure
void btSend(btType type, char *data, char destination = 0x00);

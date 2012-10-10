#ifndef ROBOT_H
#define ROBOT_H

#define HEIGHT_DISTANCE 50 //discance to move up and down lines between supply and storage tubes, cm
#define LENGTH_DISTANCE 10 //distance to move side to side between storage tubes, in cm
#define REACTOR_PATH 15 //discance to the reactor in cm

#define START_X 3 //starting x coordinate on the field
#define START_Y 2 //starting y coordinate on the field



#define SERVO_RESPONSE 10 //time servo takes to respon in milliseconds
#define START_CLAW CLOSED
/*** Use Options ***/
#define DEBUG 0

/*** Pin Definitions ***/
#define CLAW_SERVO 10
#define LIFT_SERVO 13
#define WRIST_SERVO 12

#define TOP_BUMPER 1
#define BOT_BUMPER 0
#define TOP_BUMPERPHYS 3
#define BOT_BUMPERPHYS 2
#define BUMPER_PIN 18

#define LEFT_1A 33
#define LEFT_2A 34
#define LEFT_DRIVE 8

#define RIGHT_1A 35
#define RIGHT_2A 36
#define RIGHT_DRIVE 7

#define LEFT_ENCODER 19
#define RIGHT_ENCODER 20


#define WARNING_LIGHT


/*** Hardware Constants ***/

#define ENCODER_CPR 3200
#define WHEEL_RADIUS_CM 3.4925
#define WHEEL_SPACING_CM 24.130

/*** Tuning Defines ***/
#define RIGHT_LINE_FOLLOW_PROP -0.2
#define LEFT_LINE_FOLLOW_PROP -0.2
#define LINE_SENSOR_CHARGE_US 2  //How long we charge the capacitor
#define LINE_SENSOR_READ_US 10 //How long we wait between 
#define LINE_SENSOR_CONSECUTIVE_READS 1

#define DEFSPEED 100


/*** Field Lengths ***/
#define FIELD_X 172
#define FIELD_Y 190



/*** Enums ***/
enum {REACTOR_A,REACTOR_B,NEW_1,NEW_2,NEW_3,NEW_4,SPENT_4,SPENT_3,SPENT_2,SPENT_1};

#endif

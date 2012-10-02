
/*** Use Options ***/
#define DEBUG 1

/*** Pin Definitions ***/
#define CLAW_SERVO
#define ELEVATOR_SERVO
#define WRIST_SERVO

#define BUMPER_PIN 18
#define BUMPER_INTERRUPT 5

#define LEFT_DRIVE 31
#define RIGHT_DRIVE 32

#define LEFT_ENCODER 19
#define RIGHT_ENCODER 20
#define LEFT_ENCODER_INTERRUPT 4
#define RIGHT_ENCODER_INTERRUPT 3


#define WARNING_LIGHT


/*** Hardware Constants ***/

#define ENCODER_CPR 1856
#define WHEEL_RADIUS_CM 3.4925
#define WHEEL_SPACING_CM 10

/*** Tuning Defines ***/
#define RIGHT_LINE_FOLLOW_PROP 0.7
#define LEFT_LINE_FOLLOW_PROP 0.5
#define LINE_SENSOR_CHARGE_US 5  //How long we charge the capacitor
#define LINE_SENSOR_READ_US 20 //How long we wait between 

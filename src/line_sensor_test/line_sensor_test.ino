//Code for the QRE1113 Digital board
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.
#include <avr/io.h>

#define LINE_SENSOR_COUNT 6 //don't change this really. you will break the member vars.
#define CHARGE_MICROS 10  //How long we charge the capacitor
#define READ_MICROS 1000 //How long we wait between 

class lineSensor{
  public:
  lineSensor();
  void update();
  void print();
  int sensor[LINE_SENSOR_COUNT];
  int frontLeft, frontRight, frontCenter, rearLeft, rearRight, rearCenter;
};

lineSensor::lineSensor(){ 
}

inline void lineSensor::update(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
  DDRD = B11111100;
  //digitalWrite( QRE1113_Pin, HIGH );
  PORTD = B11111100;
  delayMicroseconds(CHARGE_MICROS);
  //pinMode( QRE1113_Pin, INPUT );
  DDRD = B00000000;
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < READ_MICROS){
   if(!digitalRead(2)&&!sensor[0]) sensor[0] = 1; 
   if(!digitalRead(3)&&!sensor[1]) sensor[1] = 1; 
   if(!digitalRead(4)&&!sensor[2]) sensor[2] = 1; 
   if(!digitalRead(5)&&!sensor[3]) sensor[3] = 1; 
   if(!digitalRead(6)&&!sensor[4]) sensor[4] = 1; 
   if(!digitalRead(7)&&!sensor[5]) sensor[5] = 1; 
  }
}
void lineSensor::print(){
  int i;
  for(i=0; i<LINE_SENSOR_COUNT; i++){
    Serial.print(sensor[i]);
    sensor[i] = 0;
  }
}

lineSensor mySensor;
void setup(){
  Serial.begin(9600);
  
}


void loop(){
    mySensor.update();
    mySensor.print();
    Serial.print('\n');
}




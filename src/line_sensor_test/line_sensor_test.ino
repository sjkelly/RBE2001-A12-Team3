//Code for the QRE1113 Digital board
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.
#include <avr/io.h>

#define LINE_SENSOR_COUNT 8

class lineSensor{
  public:
  lineSensor();
  void read();
  int sensor[LINE_SENSOR_COUNT];
};

lineSensor::lineSensor(){ 
}

inline void lineSensor::read(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  //pinMode( QRE1113_Pin, OUTPUT );
  DDRD = B11111100;
  //digitalWrite( QRE1113_Pin, HIGH );
  PORTD = B11111100;
  delayMicroseconds(10);
  //pinMode( QRE1113_Pin, INPUT );
  DDRD = B00000000;
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (micros() - time < 1000){
   if(!digitalRead(2)&&!sensor[2]) sensor[2] = 1; 
   if(!digitalRead(3)&&!sensor[3]) sensor[3] = 1; 
   if(!digitalRead(4)&&!sensor[4]) sensor[4] = 1; 
   if(!digitalRead(5)&&!sensor[5]) sensor[5] = 1; 
   if(!digitalRead(6)&&!sensor[6]) sensor[6] = 1; 
   if(!digitalRead(7)&&!sensor[7]) sensor[7] = 1; 
  }
}

  lineSensor mySensor;
void setup(){
  Serial.begin(9600);
  
}
void loop(){
    mySensor.read();
      int i;
      for(i=2; i<LINE_SENSOR_COUNT; i++){
         Serial.print(mySensor.sensor[i]);
         mySensor.sensor[i] = 0;
         Serial.print(' ');
      }
      Serial.print('\n');
}





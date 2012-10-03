#include "comms.h"

void debug(LineSensor &lineSensor, Motor &leftMotor, Motor &rightMotor, Move &move){
    Serial.print("Line Sensor States:");
    Serial.println(lineSensor.state,BIN);
    Serial.print("Front Button State : ");
    Serial.println(move.checkBumper());
    Serial.print("Motor Distances (cm) >");
    Serial.print(" Left : ");
    Serial.print(leftMotor.getDistance());
    Serial.print(" Right : ");
    Serial.println(rightMotor.getDistance());
}




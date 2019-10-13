// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       TreatServoMotor.cpp
// Purpose:    This code is a cpp file for the Servo Motor dog treat dispenser project.
//             This file adds functionality to the class created in the ServoMotor header. 
#include "Arduino.h"
#include "TreatServoMotor.h"
#include <Servo.h>

Servo myservo;

////////////////////////////////
//  ServoMotor() Constructor  //
////////////////////////////////
TreatServoMotor::TreatServoMotor(int servoPin)
{ 
  this->servoPin = servoPin; 
}
 
////////////////////////////////
//      servoEvent()          //
////////////////////////////////
void TreatServoMotor::treatServoEvent()
{
  myservo.attach(servoPin);
  Serial.print("Treat Servo Event Taking Place \n");                         
  myservo.write(0); 
  delay(1000);            
  myservo.detach();                    
}

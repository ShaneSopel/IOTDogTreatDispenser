// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       CamServoMotor.h
// Purpose:    This code is a header file for the Servo Motor that controls the camera on the dog treat dispenser project.
//             This class will be used to add event base use of the Servo Motor.

#include "Arduino.h"
#include "CamServoMotor.h"
#include <Servo.h>

Servo myservo1;

////////////////////////////////
// CamServoMotor() Constructor//
////////////////////////////////
CamServoMotor::CamServoMotor(int servoPin)
{ 
  this->servoPin = servoPin; 
}
 
////////////////////////////////
//      servoEventLeft()      //
////////////////////////////////
void CamServoMotor::servoEventLeft()
{
  myservo1.attach(servoPin);
  Serial.print("Servo Moves Left\n");                         
  myservo1.write(180); 
  delay(500);            
  myservo1.detach();                    
}


 
////////////////////////////////
//      servoEventRight()     //
////////////////////////////////
void CamServoMotor::servoEventRight()
{
  myservo1.attach(servoPin);
  Serial.print("Servo Moves Right \n");                         
  myservo1.write(0); 
  delay(500);            
  myservo1.detach();                    
}

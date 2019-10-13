// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       TreatServoMotor.h
// Purpose:    This code is a header file for the Servo Motor on the dog treat dispenser project.
//             This class will be used to add event base use of the Servo Motor.  
#ifndef TREATSERVOMOTOR_H
#define TREATSERVOMOTOR_H

  class TreatServoMotor
  {
  public:

    // Constructor to set pin value of the servo motor
    TreatServoMotor(int servoPin);

    // This event will occur as a tick in the counter in webserver.cpp
    // if the mobile application calls it, the function will
    // move the servo.
    void treatServoEvent();

  private:
    //microcontroller board Pinout for servo 
    int servoPin;
    
  };

#endif

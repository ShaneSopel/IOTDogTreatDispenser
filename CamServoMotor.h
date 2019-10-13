// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       CamServoMotor.cpp
// Purpose:    This code is a cpp file for the Servo Motor that controls the camera on the dog treat dispenser project.
//             This file adds functionality to the class created in the CamServoMotor header. 

#ifndef CAMSERVOMOTOR_H
#define CAMSERVOMOTOR_H

  class CamServoMotor
  {
  public:

    // Constructor to set pin value of the servo motor
    CamServoMotor(int servoPin);

    // Turning motor of camera Left
    void servoEventLeft();

    //turning motor of camera right
    void servoEventRight();

  private:
    //microcontroller board Pinout for servo 
    int servoPin;
    
  };

#endif

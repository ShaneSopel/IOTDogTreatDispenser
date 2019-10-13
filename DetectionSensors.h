// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       PingSensor.h
// Purpose:    This code is a header file for the Ping aud audio Sensor on the dog treat dispenser project.
//             This class will be used to add event base use of the detection Sensors. 
 
#ifndef DETECTIONSENSORS_H
#define DETECTIONSENSORS_H

  class DetectionSensors
  {
  public:
    //setup Constructor
    DetectionSensors(int pingPin, int audioPin);
    
    // Event for Ping or audio sensor
    // if the sensors are tripped it will run the
    // Push notfication event function, which will send a notification to the andriod user.
    void detectionEvent();

  private:
    int pingPin;
    int audioPin;
    // the state of the PingSensor
    // if it is set to high or low
    byte state;
  };

#endif

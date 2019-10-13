// Written By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       PIRSensor.cpp
// Purpose:    This code is a cpp file for the PIR Sensor dog treat dispenser project.
//             This file adds functionality to the class created in the PIRSensor header. 
#include "Arduino.h"
#include "DetectionSensors.h"
#include "Webserver.h"

webserver webserver;

// Using Parallax Ping Function for converting the time into inches
// This allows our group to understand a distance of how far away a dog or 
// object may be from the device.
// This will intiate the servo and camera feature.
////////////////////////////////
//  microsecondsToInches      //
//////////////////////////////// 
long microsecondsToInches(long microseconds) 
{
  // The speed of sound is  74 microseconds per inch.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 74 / 2;
}


/////////////////////////////////////
//  DetectionSensors() Constructor //
/////////////////////////////////////
DetectionSensors::DetectionSensors(int pingPin, int audioPin)
{
    this->pingPin = pingPin;   
    this->audioPin = audioPin;
}

////////////////////////////////
//        detectionEvent()    //
////////////////////////////////
void DetectionSensors::detectionEvent()
{

  // establish variables for duration of the ping, and the distance result
  // in inches:
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);

  Serial.print(inches);
  Serial.print('\n');
  
  if(inches != 0)
  {  
     Serial.print("movement");
     webserver.sendNotification("A Dog was detected");
  }
  delay(150);
  
}

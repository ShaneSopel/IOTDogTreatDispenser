// Constructed By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       Webserver.h
// Purpose:    This code is a header file for the webserver functions of the dog treat dispenser project.
//             This file was created in order add the functions from the arducam library in a more functional manner
//             as well as adding an area where the event handlers from the andriod application can interact with the webserver.
//             This allows us to make and recieve calls through the web from the andriod application.  

#include <ArduCAM.h>

#ifndef WEBSERVER_H
#define WEBSERVER_H

class webserver
{
  public:

  // Setup the features of the webserver and arduCAM
  void setupFeatures();

  // The main interrupt that is used in the main loop that sends ISR 
  // calls to the rest of the operating system.
  void streamClientHandler();

  // Start the campture of the camera at system memory level.
  void start_capture();

  // Start the camera capture at the device level.
  void camCapture(ArduCAM myCAM);

  // Capture stream level data, so mutiple camera captures per second.
  void serverCapture();

  // Stream the camera captures to webserver.
  void serverStream();

  // Set the Camera resolution quality. 
  void setCamResolution(int reso);

  // clear memory data.
  void clearData();

  // ISR that tells OS to dispense treats when it receives interrupt from andriod application.
  void PushTreatEvent();

  // ISR that tells OS to send notification of movement to the andriod application.
  void sendNotification(String message);

  // ISR that tells OS to move camera to the left when it receives interrupt from andriod application
  void MoveCameraLeft();

  // ISR that tells OS to move camera to the right when it receives interrupt from andriod application
  void MoveCameraRight();

};  

#endif

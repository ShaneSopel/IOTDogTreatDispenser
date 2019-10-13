#include <FS.h> // FOR SPIFFS
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>
#include "memorysaver.h"
#include "Webserver.h"
#include "DetectionSensors.h"

webserver handler;

DetectionSensors ping(0,4);

IPAddress ip(192, 168, 150, 203);
IPAddress gateway(192, 168, 150, 1);
IPAddress subnet(255, 255, 255, 0);


////////////////////////////////
//    main setup function     //
////////////////////////////////
void setup() 
{
  handler.setupFeatures();
  Serial.begin(115200);
  Serial.println("ArduCAM Start!");

}

/////////////////////////////
//    Main loop function   //
/////////////////////////////
void loop()
{
  handler.streamClientHandler();
  ping.detectionEvent();
}

// Constructed By: Shane Sopel
// For:        University of Michigan Dearborn ECE554 Summer 2019
// Name:       Webserver.h.cpp
// Purpose:    This code is a header file for the webserver functions of the dog treat dispenser project.
//             This file was created in order add the functions from the arducam library in a more functional manner
//             as well as adding an area where the event handlers from the andriod application can interact with the webserver.
//             This allows us to make and recieve calls through the web from the andriod application.  

#include <FS.h> // FOR SPIFFS
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>
#include "webserver.h"
#include "TreatServoMotor.h"
#include "CamServoMotor.h"

TreatServoMotor tmotor(2);

CamServoMotor cammotor(5);

String deviceId = "v758BDED19949BEA";
const char* logServer = "api.pushingbox.com";

// set GPIO16 as the slave select :
const int CS = 16;

// set GPIO16 as the slave select :
//const int CS = 16;

// if the video is chopped or distored, try using a lower value for the buffer
// lower values will have fewer frames per second while streaming
static const size_t bufferSize = 4096; // 4096; //2048; //1024;

static const int fileSpaceOffset = 700000;

//AP mode configuration
const char *AP_ssid = "DogTreatDispenser";
//Default is no password.If you want to set password,put your password here
const char *AP_password = "APpassword";

//Station mode you should put your ssid and password
const char *ssid = "NETGEAR35"; // Put your SSID here
const char *password = "greatstreet231"; // Put your PASSWORD here

static IPAddress ip(192, 168, 150, 203); // static IP used for browser access: http://IPaddress
static IPAddress gateway(192, 168, 150, 1);
static IPAddress subnet(255, 255, 255, 0);

ArduCAM myCAM(OV2640, CS);
ESP8266WebServer server(8080);
//int fileTotalKB = 0;
//int fileUsedKB = 0; int fileCount = 0;
//String errMsg = "";
int imgMode = 1; // 0: stream  1: capture
int resolution = 3;


////////////////////////////////
// webserver() setupFeatures()//
////////////////////////////////

void webserver::setupFeatures()
{

   uint8_t vid, pid;
   uint8_t temp;

#if defined(__SAM3X8E__)
  Wire1.begin();
#else
  Wire.begin();
#endif

  // set the CS as an output:
  pinMode(CS, OUTPUT);

  // initialize SPI:
  SPI.begin();
  SPI.setFrequency(4000000); //4MHz

  //Change to JPEG capture mode and initialize the OV2640 module
  myCAM.set_format(JPEG);
  myCAM.InitCAM();

  webserver::setCamResolution(resolution);

  myCAM.clear_fifo_flag();


    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    WiFi.config(ip, gateway, subnet); // remove this line to use DHCP

  // setup handlers
  server.on("/treat", HTTP_GET, std::bind(&webserver::PushTreatEvent, this));
  server.on("/stream", HTTP_GET, std::bind(&webserver::serverStream, this));
  server.on("/left", HTTP_GET, std::bind(&webserver::MoveCameraLeft, this));
  server.on("/right", HTTP_GET, std::bind(&webserver::MoveCameraRight, this));
  
  //server.onNotFound(handleNotFound);
  server.begin();

}

//////////////////////////////////////
// webserver() streamClientHandler()//
//////////////////////////////////////

void webserver::streamClientHandler()
{
  server.handleClient();
}

//////////////////////////////////////
// webserver()   PushTreatEvent()   //
//////////////////////////////////////
void webserver::PushTreatEvent()
{
 
  WiFiClient client = server.client();
  
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);


   while (client.connected()) 
   {
      tmotor.treatServoEvent(); 
      break;
   }
  
}

//////////////////////////////////////
// webserver()   MoveCameraLeft()   //
//////////////////////////////////////
void webserver::MoveCameraLeft()
{
    WiFiClient client = server.client();  

  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);


   while (client.connected()) 
   {
      cammotor.servoEventLeft(); 
      break;
   }
}

//////////////////////////////////////
// webserver()   MoveCameraRight()  //
//////////////////////////////////////
void webserver::MoveCameraRight()
{
       WiFiClient client = server.client();  

  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);


   while (client.connected()) 
   {
      cammotor.servoEventRight(); 
      break;
   }
}


//////////////////////////////////////
// webserver()   sendNotification() //
//////////////////////////////////////
void webserver::sendNotification(String message)
{

  Serial.println("- connecting to Home Router SID: " + String(ssid));
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  
  WiFiClient client;

  Serial.println("- connecting to pushing server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    
    String postStr = "devid=";
    postStr += String(deviceId);
    postStr += "&message_parameter=";
    postStr += String(message);
    postStr += "\r\n\r\n";
    
    Serial.println("- sending data...");
    
    client.print("POST /pushingbox HTTP/1.1\n");
    client.print("Host: api.pushingbox.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
}


//////////////////////////////////////
// webserver()   start_capture()    //
//////////////////////////////////////
void webserver::start_capture() 
{
  myCAM.clear_fifo_flag();
  myCAM.start_capture();
}

/////////////////////////////////////////////
// webserver()    camCapture(ArduCAM myCAM)//
/////////////////////////////////////////////
void webserver::camCapture(ArduCAM myCAM) 
{

  WiFiClient client = server.client();

  size_t len = myCAM.read_fifo_length();
  if (len >= 0x07ffff) {
    Serial.println("Over size.");
    return;
  } else if (len == 0 ) {
    Serial.println("Size is 0.");
    return;
  }

  myCAM.CS_LOW();
  myCAM.set_fifo_burst();
  
  if (!client.connected()) return;

  static uint8_t buffer[bufferSize] = {0xFF};

  while (len) {
    size_t will_copy = (len < bufferSize) ? len : bufferSize;
    SPI.transferBytes(&buffer[0], &buffer[0], will_copy);
    if (!client.connected()) break;
    client.write(&buffer[0], will_copy);
    len -= will_copy;
  }

  myCAM.CS_HIGH();
}

/////////////////////////////////////////////
//     webserver serverCapture()           //
/////////////////////////////////////////////
void webserver::serverCapture() {


  start_capture();
  Serial.println("CAM Capturing");

  int total_time = 0;

  total_time = millis();
  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));
  total_time = millis() - total_time;
  Serial.print("capture total_time used (in miliseconds):");
  Serial.println(total_time, DEC);

  total_time = 0;

  Serial.println("CAM Capture Done!");
  total_time = millis();
  camCapture(myCAM);
  total_time = millis() - total_time;
  Serial.print("send total_time used (in miliseconds):");
  Serial.println(total_time, DEC);
  Serial.println("CAM send Done!");
}

///////////////////////////////
// webserver() serverStream  //
///////////////////////////////
void webserver::serverStream() {
  WiFiClient client = server.client();

  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);

while (client.connected()) 
{
    start_capture();

    while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));

    size_t len = myCAM.read_fifo_length();
    if (len >= 0x07ffff) {
      Serial.println("Over size.");
      continue;
    } else if (len == 0 ) {
      Serial.println("Size is 0.");
      continue;
    }

    myCAM.CS_LOW();
    myCAM.set_fifo_burst();  

     

    if (!client.connected()) break;
    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n\r\n";
    server.sendContent(response);

    static uint8_t buffer[bufferSize] = {0xFF};

    while (len) {
      size_t will_copy = (len < bufferSize) ? len : bufferSize;
      SPI.transferBytes(&buffer[0], &buffer[0], will_copy);
      if (!client.connected()) break;
      client.write(&buffer[0], will_copy);
      len -= will_copy;
    }
    myCAM.CS_HIGH();

    if (!client.connected()) break;
  }
}

/////////////////////////////////////////////
// webserver() setCamResolution(int reso)  //
/////////////////////////////////////////////
void webserver::setCamResolution(int reso)
{

/*    
      myCAM.OV2640_set_JPEG_size(OV2640_160x120);
    
      myCAM.OV2640_set_JPEG_size(OV2640_176x144);
    
      myCAM.OV2640_set_JPEG_size(OV2640_320x240);

*/

      myCAM.OV2640_set_JPEG_size(OV2640_352x288);


     // myCAM.OV2640_set_JPEG_size(OV2640_640x480);

     // myCAM.OV2640_set_JPEG_size(OV2640_800x600);

     //myCAM.OV2640_set_JPEG_size(OV2640_1024x768);

     // myCAM.OV2640_set_JPEG_size(OV2640_1280x1024);

    //  myCAM.OV2640_set_JPEG_size(OV2640_1600x1200);

}

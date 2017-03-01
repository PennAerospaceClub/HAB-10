#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
#include <SPI.h>
#include <SD.h>

//RockBlock libraries
#include <Time.h>
//#include <TimeLib.h>

#include <QueueArray.h>
#include <IridiumSBD.h>
#include <SoftwareSerial.h>
#include "Message/Message.cpp"

/* Assign a unique ID to the sensors */
Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

//RockBlock variables
int rxPin = 10;
int txPin = 11;
int sleepPin = 8;
QueueArray<Message> recMsgs;
QueueArray<Message> sentMsgs;

SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);
uint8_t buffer[200];
 int signalQuality = -1;

//gps variables
long int latit = -1;
long int longit = -1;
long int alt = -1;
long int gpstime = -1;
long int numsats = -1; 
String dataString;

TinyGPSPlus gps;

const int chipSelect = 53;

float yaw;
float pitch;
float roll;

//sanity stuff
boolean sd = false;  
boolean imu = false;
boolean sane = false;
boolean gpsworking = false;
boolean rockb = false;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  
   //Rockblock initialization
//  nss.begin(19200);
//
//  isbd.attachConsole(Serial);
//  isbd.setPowerProfile(0);
//  isbd.begin();

  delay(10); 

  //Rockblock initialization
  nss.begin(19200);

  isbd.attachConsole(Serial);
  isbd.setPowerProfile(0);
  isbd.begin();
}

void loop() {
  while(!sane){
    sanity();
  }
  readIMU();
  readGPS();
  dataString = (String)yaw + ","+ (String)pitch+ "," +(String)roll+ "," +
  (String)latit + "," + (String)longit + "," + (String)alt + "," + (String)gpstime + "," 
  + (String)numsats;
  writeSD(dataString);

  Message* sendm = new Message(14857, "TEST", RCV);
  Serial.print("Message timestamp: ");
  Serial.println(sendm -> timestamp);
//  Message* sendm = new Message(14857, "TEST", RCV);
//  Serial.print("Message timestamp: ");
//  Serial.println(sendm -> timestamp);
}

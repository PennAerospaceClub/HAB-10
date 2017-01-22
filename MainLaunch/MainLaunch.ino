#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
#include <SPI.h>
#include <SD.h>

/* Assign a unique ID to the sensors */
Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

long int lat = -1;
long int longit = -1;
long int alt = -1;


const int chipSelect = 53;

float yaw;
float pitch;
float roll;

//sanity stuff
boolean sd = false;  
boolean imu = false;
boolean sane = false;

void setup() {
  Serial.begin(9600);
  delay(10);
}

void loop() {
  while(!sane){
    sanity();
  }
  readIMU();
   
}

void sanity(){
  
  if(!sd){
    if (SD.begin(chipSelect)) {
      Serial.println("SD Work");
      sd = true;
    }
    else{
      Serial.println("Card failed, or not present");
    }
  }
  if(!imu){
    if(initSensors()){
      imu = true;
      Serial.println("IMU Worked");
    }
    else{
      Serial.println("IMU failed");
    }
  }
  

  sane = imu && sd;
}


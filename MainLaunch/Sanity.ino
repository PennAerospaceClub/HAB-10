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

<<<<<<< Updated upstream
  //RockBlock Sanity
//  int err = isbd.getSignalQuality(signalQuality);
//  if (!rockb){
//  if ( err != 0)
//  {
//    Serial.print("RockBlock SignalQuality failed: error ");
//    Serial.println(err);
//  }else{
//    rockb = true;
//    Serial.print("RockBlock signal quality is ");
//    Serial.println(signalQuality);
//  }
=======
<<<<<<< Updated upstream
  //  if(!Serial1.available()){
//    Serial.println("gps sending no data");
>>>>>>> Stashed changes
//  }

  if(!Serial1.available()){
   Serial.println("gps sending no data");
   }

  sane = imu && sd;
=======
  //RockBlock Sanity
  int err = isbd.getSignalQuality(signalQuality);
  if (!rockb){
  if ( err != 0)
  {
    Serial.print("RockBlock SignalQuality failed: error ");
    Serial.println(err);
  }else{
    rockb = true;
    Serial.print("RockBlock signal quality is ");
    Serial.println(signalQuality);
  }
  }

  if(!Serial1.available()){
   Serial.println("gps sending no data");
   }

  sane = imu && sd&&rockb;
>>>>>>> Stashed changes
}


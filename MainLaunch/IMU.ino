boolean initSensors()
{
  if(!accel.begin()){
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    return false;
  }
  if(!mag.begin()){
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    return false;
  } 
  return true;
}

void readIMU(){
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;

  /* Read the accelerometer and magnetometer */
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);



  /* Use the new fusionGetOrientation function to merge accel/mag data */  
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
      yaw = orientation.heading;
  pitch = orientation.pitch;
  roll = orientation.roll;
    /* 'orientation' should have valid .roll and .pitch fields */
    Serial.print(F("Orientation: "));
    Serial.print(roll);
    Serial.print(F(" "));
    Serial.print(pitch);
    Serial.print(F(" "));
    Serial.print(yaw);
    Serial.println(F(""));
  }
}


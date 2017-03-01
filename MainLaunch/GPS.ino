//readGPS: parses GPPGA input if available and stores data to
//"lat", "longit", and "alt"
void readGPS(){
 Serial.println("reading gps");
 smartDelay(1000);
 latit = gps.location.lat();
 longit = gps.location.lng();
 alt = gps.altitude.meters();
 gpstime = gps.time.value();
 numsats = gps.satellites.value();
}

static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do 
  {
    while (Serial1.available() && (!gps.altitude.isUpdated()) )
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

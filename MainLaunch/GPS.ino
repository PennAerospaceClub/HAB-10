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
Serial.println(dataString);

//  
//  
//  boolean gooddata = false;
//  String field = "";
//  while(!gooddata){
//    delay(20);
//    int gpsMaxSearchTime = millis() + 5000;
//    Serial.println("revisiting gps");
//    while(Serial1.available() && gpsMaxSearchTime > millis()){
//      if((char)Serial1.read() == '$'){
//        int i = 0;
//        while(i < 75){
//          if(Serial1.available()){
//            field += (char)Serial1.read();
//            i++;
//          }
//        }
//        //Serial.println(field);
//        if(field.startsWith("GPGGA")){
//          //Serial.println(field);
//          gooddata = true;
//  
//          int index1 = 0;
//          int index2 = 0;
//          
//          //gpgga,time,latitude,longitude,fixquality,numsats,dilut,altitude,stuff,stuff,checksum
//          //time//
//          index1 = field.indexOf(",");
//          index2 = field.indexOf(",", index1 + 1);
//          gpstime = field.substring(index1 + 1, index2).toInt();
//          index1 = index2;
//          //Serial.println("time = " + (String)gpstime);
//          //latitude//
//          index2 = field.indexOf(",", index1 + 1);
//          lat = field.substring(index1 + 1, index2).toInt();
//          index1 = index2;
//          //Serial.println("lat = " + (String)lat);
//          //skip//
//          index2 = field.indexOf(",", index1 + 1);
//          index1 = index2;
//          //longitude//
//          index2 = field.indexOf(",", index1 + 1);
//          longit = field.substring(index1 + 1, index2).toInt();
//          index1 = index2;
//          //Serial.println("longit = " + (String)longit);
//          //skip//
//          index2 = field.indexOf(",", index1 + 1);
//          index1 = index2;
//          //skip//
//          index2 = field.indexOf(",", index1 + 1);
//          index1 = index2;
//          //numsats//
//          index2 = field.indexOf(",", index1 + 1);
//          numsats = field.substring(index1 + 1, index2).toInt();
//          index1 = index2;
//          //Serial.println("numsats = " + (String)numsats);
//          //skip//
//          index2 = field.indexOf(",", index1 + 1);
//          index1 = index2;
//          //altitude//
//          index2 = field.indexOf(",", index1 + 1);
//          alt = field.substring(index1 + 1, index2).toInt();
//          index1 = index2;
//          //Serial.println("alt = " + (String)alt);
//          field = "";
//          
//          field = "";
//        }
//        else{
//          field = "";
//        }
//      }
//      else{
//        field = "";
//      }
//    }
//  }
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available() && (!gps.altitude.isUpdated()) )
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

//readGPS: parses GPPGA input if available and stores data to
//"lat", "longit", and "alt"
void readGPS(){
  boolean gooddata = false;
  int gpsMaxSearchTime = millis() + 5000;
  String field = "";
  while(!gooddata){
    while(Serial1.available() && gpsMaxSearchTime > millis()){
      if((char)Serial1.read() == '$'){
        int i = 0;
        while(i < 75){
          if(Serial1.available()){
            field += (char)Serial1.read();
            i++;
          }
        }
        //Serial.println(field);
        if(field.startsWith("GPGGA")){
          //Serial.println(field);
          gooddata = true;
  
          int index1 = 0;
          int index2 = 0;
          
          //gpgga,time,latitude,longitude,fixquality,numsats,dilut,altitude,stuff,stuff,checksum
          //time//
          index1 = field.indexOf(",");
          index2 = field.indexOf(",", index1 + 1);
          gpstime = field.substring(index1 + 1, index2).toInt();
          index1 = index2;
          //latitude//
          index2 = field.indexOf(",", index1 + 1);
          lat = field.substring(index1 + 1, index2).toInt();
          index1 = index2;
          //longitude//
          index2 = field.indexOf(",", index1 + 1);
          longit = field.substring(index1 + 1, index2).toInt();
          index1 = index2;
          //skip//
          index2 = field.indexOf(",", index1 + 1);
          index1 = index2;
          //numsats//
          index2 = field.indexOf(",", index1 + 1);
          numsats = field.substring(index1 + 1, index2).toInt();
          index1 = index2;
          //skip//
          index2 = field.indexOf(",", index1 + 1);
          index1 = index2;
          //altitude//
          index2 = field.indexOf(",", index1 + 1);
          alt = field.substring(index1 + 1, index2).toInt();
          index1 = index2;
          field = "";
          
          field = "";
        }
        else{
          field = "";
        }
      }
      else{
        field = "";
      }
    }
  }
}

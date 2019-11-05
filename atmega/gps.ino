//store nmea split data
String data[20];

String getNmea() {
  //think of reseting module if there is no data
   byte timeout=0;
   char *nmea=""; 
   while (!SendExpect("AT+GPS=1", "OK",500));
   while (!SendExpect("AT+GPSRD=3", "OK",1000));  
   Serial.flush();
   while (true) {
    //break o the loop if the module takes too long to answer
    //if(timeout>=200)break;
    if (Serial.available()) {
      String data=Serial.readString();
      //Serial.readBytesUntil('\r',nmea,80);           
      if ( contains(data, "+GPSRD:") && contains(data,"$")) {
        return data.substring(data.indexOf("+GPSRD:") + 7);
      }else return "";               
    }
    //delay(30);
   // timeout++;  
  }
}
String fetchNmea(String nmea){
     //get first line of the nmea string 
     nmea=nmea.substring(0,nmea.indexOf('\n'));
     split(nmea,',',data,20); 
    //0 is manufacturer index , 2 & 4 latitude/long 
    if(contains(data[0],"GPGGA") && data[2]!="" && data[4]!=""){
      while (!SendExpect("AT+GPS=0", "OK"));
      //debug(data[4]);
      //global variable to end search and restart when neccessary
      gps_tag=false;
      return nmea;      
    }else return "";      
}
void getGps(){
  gps_tag=true;
  while(gps_tag){
    myNmea=fetchNmea(getNmea());
    delay(20);
  }
}

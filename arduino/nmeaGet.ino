/*
Configure GPS
GET Data String of GPRSD

Example of Return:
$GPGGA,174623.000,3645.02877,N,00303.22178,E,1,08,1.2,222.6,M,,M,,0000*48
$GPGSA,A,3,08,03,22,17,01,11,14,32,,,,,1.9,1.2,1.5*35
$GPGSV,3,1,11,08,39,164,28,03,55,258,35,22,77,311,31,17,16,319,44*71
$GPGSV,3,2,11,01,66,351,50,11,82,067,39,14,35,060,47,32,21,045,44*7F
$GPGSV,3,3,11,31,01,098,,28,21,277,,27,07,152,*44
$GPRMC,174623.000,A,3645.02877,N,00303.22178,E,0.00,0.00,220717,,,A*6A
$GPVTG,0.00,T,,M,0.00,N,0.00,K,A*3D
*/

//Khaled+Abdou
String getNMEA() {
  //think of reseting module if there is no data
   byte timeout=0; 
   while (!SendCommand("AT+GPS=1", "OK",500));
   while (!SendCommand("AT+GPSRD=3", "OK",2000)); 
  delay(100);
  
  Serial.flush();
  while (true) {
    //break o the loop if the module takes too long to answer
    if(timeout>=200)break;
    if (Serial.available()) {
      //use Serial.readBytes() or Serial.read() may be better
      String data = Serial.readString();
      if ( contains(data, "+GPSRD:") && contains(data,"$")) {
        return data.substring(data.indexOf("+GPSRD:") + 7);
      }else  return "";         
    }
    //change this and the timeout break value to calibrate more
    delay(30);
    timeout++;
  }
}

void nmea_fetch(String nmea){
split(nmea,'\n',satelites,6);
for(byte i=0;i<6;i++){
  split(satelites[i],',',data,25); 
  if(satelites[i].length()>50){        
    //0 is manufacturer index , 3/2 latitude/long index check again
    if(contains(data[0],"GPGGA") && data[2]!=""){   
    times=data[1];
    latitude=data[2];
    longitude=data[4];
    }else if(contains(data[0],"GPRMC") && data[3]!=""){
    times=data[1];
    latitude=data[3];
    longitude=data[5];  
    }else if(contains(data[0],"GPGLL") && data[3]!=""){
    times=data[5];
    latitude=data[1];
    longitude=data[3];
    }
  }  
  }
  if(longitude!="" && times!="" && latitude!=""){
    //disable gps when location strings are not null
    while (!SendCommand("AT+GPS=0", "OK"));
  //Serial.print("final data: ");
  //Serial.println(longitude);
  //Serial.println(latitude);
  //Serial.println(times);
    Serial.flush();
    //global variable to end search and restart when neccessary
    gps_tag=false;      
  }        
}

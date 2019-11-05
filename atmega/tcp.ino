bool cgatt(byte rst = 2);
byte creg(){
    
  if(config_tag)RomConfig();
  if(sms_tag)smsInterupt();
  
    Serial.flush();
    Serial.write("AT+CREG?");
    Serial.write('\r');
    
    delay(1000);
    String creg_string=Serial.readString();
  if (contains(creg_string, "+CREG:")) {
    creg_string = creg_string.charAt(creg_string.indexOf(",") + 1);
  }else creg_string="4";
  return (byte) creg_string.toInt();   
}
bool config_gprs(byte rst = 0) {
  if (rst >= 3) {
    reset();
    return false;
  }
  rst++;
  switch (creg()) {
    case 1:
    case 5:
      if (cgatt())return true;
      break; 
      default:
      delay(2000);
      break;
  }
  return config_gprs(rst);
}
bool cgatt(byte rst = 2) {
  //attach gprs
  if (rst <= 0) return false;
  rst--;
  if (!SendExpect("AT+CGATT?", "+CGATT:1")) {
    SendExpect("AT+CGATT=1", "OK", 4000);
    delay(500);
    return cgatt(rst);
  } else return true;
}

bool sendTCP(String request,byte req=1) {
  //req 1 is POST (data & credit) ,2 is GET (config) 
  if (config_gprs()) {
    if (!SendExpect("AT+CIPSTATUS", "CONNECT")) {
      if ( SendExpect("AT+CIPSTART=\"TCP\",\"api.alzadenz.com\",80", "CONNECT OK", 10000)) {
        delay(500);
        Serial.flush();
        return cipSend(request,req);
      }
    } else {
      return cipSend(request,req);
    }
  }
  return false;
}
bool cipSend(String request,byte req) {
  //req 1 is POST (data & credit) ,2 is GET (config) (we have to read data from the tcp stream not just return true
  if (SendExpect("AT+CIPSEND", ">", 4000)) {
  Serial.print(request);
    //POST
    if(req==1){    
      if (SendExpect((char)26, "Done",12000,1))
        {
          Serial.flush();
          return true;
        }
    }else{
    //GET          
    }
  }
  delay(1000);
  return false;
}


char *sosNumber="";

bool sendSms(String message) {
  String resp = "";
  Serial.flush();
  if (SendExpect("AT+CMGF=1", "OK", 4000)) {
    char cmd[20] = {0};
    //ugly programming think of somethin else
    //concat 2 array characters into one
    pointerFusion("AT+CMGS=", sosNumber, cmd);
    if (SendExpect(cmd, ">", 2000)) {
      delay(5);
      //can't use write on a string
      Serial.print(message);
      //hex rep of (char)26
      if (SendExpect((char)26, "OK", 20000,1))
      {
        return true;
      } else return false;

    }
  }
}


void smsInterupt(){
  //getGps();
  String message="replace with content";
  while(!sendSms(message));
  //clear sms flag to send only one message ( see main program )
  sms_tag=false;
}

/*
activate PDU mode (sms data service)
AT+CMGF=1
OK
AT+CMGS="00213663171018"

> Fuck you sent from A7
 //Special char to end the waiting (char)26 in asci

+CMGS: 1

OK

*/

String sosNumber="0021367002323";

bool sendSMS(String message)
{             
  //Set the SMS in text mode
  if (SendCommand("AT+CMGF=1","OK",5000)){
    if (SendCommand("AT+CMGS="+sosNumber,">",2000)){
      Serial.print(message);
      if(SendCommand((String)(char)26,"OK",2000)){
        return true;
      }
    }
  }
}
void smsInterupt(){
  getGps();
  String message=latitude+","+longitude;
  while(!sendSMS(message));
  //clear sms flag to send only one message ( see main program )
  sms_tag=false;
}

//get ussd response
String getCredit(char *ussd){
  
  String resp="";
  bool empty=true;
  Serial.flush();
  Serial.write(ussd);
  Serial.write('\r');
  delay(100);
  long Time= millis();
  while ((Time + 5000)> millis())                                              
    {
      resp += Serial.readString();                                                  
      if (contains(resp, "OK")) {
        empty=false;                                             
        break;                                                                                            
      }
    }
 String data[5]="";
 split(resp,'"',data,5); 
 if (empty)return "";
 //3 is the index of the returned string
 else return data[3];
  
}
/*if(SendExpect("at+cscs=\"GSM\"","OK")){
  
String s=getCredit("at+cusd=1,\"*710#\",15");
if(s!=""){
  digitalWrite(13,1);
  debug.println(s);
}
else {
  digitalWrite(13,0);
  debug.println("empty string");
}
}else digitalWrite(13,0);
delay(1000);
Serial.flush();
*/


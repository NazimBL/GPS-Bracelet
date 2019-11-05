/*
This file contains the String management and 

*/
//Nazim
void split(String NMEA,char splitChar,String data[],byte dataSize){
  long j=0;
  //check variable 
  long k=0;
  //flush previous array if any
  for(byte a=0;a<dataSize;a++)data[a]="";
  for(byte i=0;j<NMEA.length();i++){ 
        while(NMEA.charAt(j)!=splitChar){
            if(k>3)break;
            if(NMEA.charAt(j)=='\0')k++;
            data[i].concat(NMEA.charAt(j));                     
            j++;                      
         }
        j++;               
 }  
}
//Nazim
bool contains(String cmd, String resp)
{
  int i=0;
  int index=cmd.indexOf(resp);

  if(index >=0)  return true;
  if(index == -1) return false;
}



//Khaled & Abdou

/**
  * @desc Send AT Command and wait for response
  * @param string command - the At command to be sent
  * @param string response  - the awaited response from the module
  * @param int timeout - the time to wait for a response from the module
  * @return bool - success or failure
*/

boolean  SendCommand(String command, String response, int timeout = 400) {          // timeout set by defalt to 400 ms 
  String resp = "";
  Serial.flush();
  Serial.println(command);                                                          // Send the command
  delay(10);
  long int Time = millis();                                                         // take the sending command's time
  while ( (Time + timeout) > millis())                                              // wait for response from the module until the timeout is over
    {
      resp += Serial.readString();                                                  
      if (contains(resp, response)) break;                                          // if the response contains the awaited response break the loop                                      
    }
    Serial.flush();
    return contains(resp, response);                                                // if the response contains the awaited response returns 1 else 0
}

byte creg(){
  //when interrupt flag is true return this to get out of tcp loop  (see config_gprs function) 
  if(sms_tag)return (byte)21;
    Serial.flush();
    Serial.println("AT+CREG?");
    delay(1000);
    String creg_string=Serial.readString();
  if (contains(creg_string, "+CREG:")) {
    creg_string = creg_string.charAt(creg_string.indexOf(",") + 1);
  }else creg_string="4";
  return (byte) creg_string.toInt();   
}

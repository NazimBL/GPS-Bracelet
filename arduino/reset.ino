/*
void reset(){
  Serial.flush();
  Serial.println("AT+RST=1");
  Serial.setTimeout(10000);
  String response=Serial.readString();
  
  if(contains(response,"CREG")) {
    
  }else {
    reset();
  }
}
*/
void reset(){
  Serial.flush();
  Serial.println("AT+RST=1");
  delay(15000);
  Serial.flush();
}

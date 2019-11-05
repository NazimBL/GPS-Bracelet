
void RomWrite(byte prescaller,char *value){
  
  //replace 11 with data length(10+1 = 10 phhone number chars / 1 for the time scale
  byte address=0;
  while(address<11){
  EEPROM.write(address,value[address]);
  address++;
  } 
  EEPROM.write(address,prescaller);
  
}
void RomRead(char *destination){
  
  byte address=0;
  while(address<11){
    *destination=EEPROM.read(address);
     destination++;
     address++;
  }
      
}

void RomConfig(){
//change sos number and time scale
digitalWrite(4,1);
delay(500);
digitalWrite(4,0);
delay(500);
config_tag=false;  
}

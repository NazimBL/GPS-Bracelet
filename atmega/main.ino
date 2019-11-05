//#include<SoftwareSerial.h>
//SoftwareSerial debug(4,5);
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <EEPROM.h>

bool sendTCP(String request,byte req=1);
bool SendExpect(char *command, char *response, int timeout = 400, byte op=0);
String data[20];
String myNmea="";
bool gps_tag=true,sms_tag=false,config_tag=true,getConfig=false,on=true,criticalOff=false;
byte tcpCount=1,waitPrescaller=1;
long waitTime=5000;

void setup() {

attachInterrupt(digitalPinToInterrupt(2), interrupt1_call , RISING);
attachInterrupt(digitalPinToInterrupt(3), interrupt2_call  , FALLING);
Serial.begin(115200);
//debuging leds  
pinMode(4,OUTPUT);
pinMode(9,OUTPUT);
//debug.begin(115200);
//initialize power consumption features
powerInit();

}

void loop() {
//get battery level of the device and manage leds and criticalOff tag
BatteryStatus();  
//if the user didn't click on off button and if battery status is ok   
if(on && !criticalOff){
  //write cofig to rom
  if(getConfig){
    //get request
    //rom write
    config_tag=true;
    getConfig=false;
  }    
  //Read config from rom 
  //if(config_tag)RomConfig();
  turnOnA7();
  
  if(sms_tag)smsInterupt();
  //getGps();    
  //String request="POST http://api.alzadenz.com/thing/data\nthing-id: 1\ntoken: 123456789123456789\nContent-Type: nmea\n$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";  
  String request="GET http://api.alzadenz.com\r\n";
  while(!sendTCP(request));
  //tcpCount++;
  if(tcpCount%10==0){
  //POST credit
  request="GET http://46.101.207.185/api.php?id=4&data="+getCredit("AT+CUSD=1,\"*710#\",15")+"\r\n";
  while(!sendTCP(request));      
  }
  //1 is idle mode
  sleep(1);
  delay(waitTime*waitPrescaller);
  power_usart0_enable();

  }else {
    //2 is power down mode (shutdown mode)
    sleep(2); 
  }  
}

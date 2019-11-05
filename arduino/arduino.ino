
String latitude="",longitude="",times="";
String satelites[6];
String data[25];
long timestamp=6000;
bool sendTCP(String request);
bool gps_tag=true,sms_tag=false;
byte interupt_pin=2;


void setup() {  
pinMode(interupt_pin, INPUT);
attachInterrupt(digitalPinToInterrupt(interupt_pin),interrupt_call, RISING);
Serial.begin(115200);
}

void loop() {

//loop till we get accurate location
getGps();
//if interupt flag is true , get gps loc and send it by sms
if(sms_tag)smsInterupt();
String request="GET http://46.101.207.185/api.php?id=4&data="+latitude;
//loop till we receive tcp sent
while(!sendTCP(request)); 
delay(timestamp);
//flush to not get previous data
longitude="";
times="";
latitude="";
}

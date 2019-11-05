long interrupt_temp;
long interrupt_temp2;
long interrupt_times;
byte  interrupt_count = 0;
int  interrupt_clickmax = 9000;
int  interrupt_clickmini = 100;
int longint = 1000;

 attachInterrupt(digitalPinToInterrupt(2), interrupt1_call , RISING);
 attachInterrupt(digitalPinToInterrupt(3), interrupt2_call  , FALLING);


void interrupt1_call()
{
  interrupt_temp = millis();
  Serial.print(interrupt_count);
  if (interrupt_count == 0) {
    interrupt_count++;
    interrupt_times = interrupt_temp;
  } else if (interrupt_count == 1) {
    if (((interrupt_temp - interrupt_times) > interrupt_clickmini) && ((interrupt_temp - interrupt_times) < interrupt_clickmax)) {
      interrupt_times = interrupt_temp;
      interrupt_count++;
    } else if ((interrupt_temp - interrupt_times) >= interrupt_clickmax) {
      interrupt_count = 1;
      interrupt_times = interrupt_temp;
    }
  } else if (interrupt_count == 2) {
    if (((interrupt_temp - interrupt_times) > interrupt_clickmini) && ((interrupt_temp - interrupt_times) < interrupt_clickmax)) {
      interrupt_times = interrupt_temp;
      interrupt_count++;
    } else if ((interrupt_temp - interrupt_times) > interrupt_clickmax) {
      interrupt_count = 1;
      interrupt_times = interrupt_temp;
    }
  }
  if (interrupt_count == 3) {
    interrupt_times = interrupt_temp;
    interrupt_count = 0;
    interrupt_sucess();
  }
}

void interrupt_sucess() {
  //after three clicks get gps location  then send SMS
  //turn gps flag off and sms flag on (see main program )
  sms_tag = true;
 interrupt_count = 0;
}


int interrupt2_call() {

  interrupt_temp2 = millis();
  if ((interrupt_temp2 - interrupt_temp) > longint)
  {
    getConfig = true;
  }
}

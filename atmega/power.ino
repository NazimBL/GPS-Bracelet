void powerInit(){
//desactivate ADC and Comparator  
//ADCSRA=0x00; 
//ACSR=0x80;
//replace with register when final pinsare decicided
pinMode(8,INPUT);
pinMode(7,OUTPUT);
digitalWrite(8,0);
digitalWrite(7,0);
powerInterruptSetup(8);

}
void sleep(byte sleepMode)
{ 
   //switch off A7
   SendExpect("AT+CPOF","OK");
   if(sleepMode==1){
      set_sleep_mode(SLEEP_MODE_IDLE);
      // Set sleep enable (SE) bit:
      sleep_enable();
      power_adc_disable();
      power_twi_disable();
      power_spi_disable();
      power_usart0_disable(); //Needed for serial.print
      //power_timer0_disable(); //Needed for delay and millis()
      power_timer1_disable();
      power_timer2_disable(); 
            
    }else{
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      power_all_disable();      
    }
    // Put the device to sleep:
      sleep_mode();
      sleep_cpu ();  
}
double readVBAT() {
  long result;
  power_adc_enable();
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  
  power_adc_disable();
  unsigned int ADCValue;
  double Voltage;
  
  Voltage = result/1000.0;
  ADCValue = analogRead(0);
  Voltage = (ADCValue / 1024.0) * Voltage;
  return Voltage;
}
void BatteryStatus(){
 double level=readVBAT();
 if(level>=3.6)//green led;
 else if(level>=3.4 && level<3.6)//orange
 else if(level<3.4 && level>3.3)//Red
 
 else if(level=<3.3) {
    //blinkin red
    criticalOff=true;
 }
   
}   
void turnOnA7(){
  digitalWrite(7,1);
  delay(2100);
  digitalWrite(7,0);
  delay(1000);
}
void powerInterruptSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
ISR (PCINT0_vect) 
 {   
     //follow copybook diagram 
     on=!on;
 }


#include "ADS795X.h"
#include "SPI.h"

#define MHZ 1000000UL

ADS795X adcDevice;

controlRegisterMode CRM;

//Define the TLC5925 LED Driver control pins.
#define OE  7
#define LE  6
#define SDI  5
#define CLK  4


void setup() {
  Serial.begin(115200);
   //TLC5925 LED Driver control pins defined as digital output pins
  pinMode(LE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SDI, OUTPUT);
   
  redLed();
  
  // put your setup code here, to run once:
  adcDevice.slave_select_pin = 53;
  adcDevice.auto1_active_channels = 0x07;
  adcDevice.initCommunication(SPI, 8*MHZ, MSBFIRST, SPI_MODE0);
  
  CRM.bit_access_manual.mode = MANUAL_MODE;
  CRM.bit_access_manual.enable_programming = 0x01;
  CRM.bit_access_manual.next_channel = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.operation_mode = 0x00;
  CRM.bit_access_manual.output_address_mode = 0x00;
  
  adcDevice.setFunctionalMode(CRM);
}

void loop() {

  delay(300);
  Serial.println(adcDevice.readData(0x00));
  delay(300);
  Serial.println(adcDevice.readData(0x01));
  delay(300);
  Serial.println(adcDevice.readData(0x02));

}

 
void redLed()
{
       //Pins startup conditions
       digitalWrite(LE, LOW); //LE must be low while data is being shifted in
       digitalWrite(CLK, LOW); //Data shifted with CLK rising edge. This makes sure the CLK starts in LOW position
       digitalWrite(OE, HIGH); //OE high keep leds turned off while data is shifted in
 
       //Shift out the data to turn green led on: 0000 0000 0000 0010. shiftOut() shifts 1 byte at a time, so the function is called twice.
       shiftOut(SDI, CLK, MSBFIRST, 0b00000000); //First byte corresponding to outputs 15 to 8. ALL UNUSED
       shiftOut(SDI, CLK, MSBFIRST, 0b00100000); //First byte corresponding to outputs 7 to 0. 7 to 5 unused. 1 in output 2 to turn green LED on.
 
 
       //LE toggled to latch in the shifted data
       digitalWrite(LE, HIGH);
       digitalWrite(LE, LOW);
       digitalWrite(OE, LOW);
}
 



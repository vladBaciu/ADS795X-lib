
#include "ADS795X.h"
#include "SPI.h"

#define MHZ 1000000UL

#define MULTIPLEXING_MODE               (MANUAL_MODE)
#define NEXT_CHANNEL_AUTO_MODE          (0x00)

ADS795X adcDevice;

controlRegisterMode CRM;

void setup() {
  
  Serial.begin(115200);
 
  adcDevice.slave_select_pin = 53;
  adcDevice.auto1_active_channels = 0x07;
  adcDevice.initCommunication(SPI, 8*MHZ, MSBFIRST, SPI_MODE0);
  
#if(MULTIPLEXING_MODE == MANUAL_MODE)

  CRM.bit_access_manual.mode = MANUAL_MODE;
  CRM.bit_access_manual.enable_programming = 0x01;
  CRM.bit_access_manual.next_channel = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.operation_mode = 0x00;
  CRM.bit_access_manual.output_address_mode = 0x00;
  CRM.bit_access_manual.enable_programming =0x01;
#elif(MULTIPLEXING_MODE = AUTO1_MODE)

  CRM.bit_access_auto.mode = AUTO1_MODE;
  CRM.bit_access_auto.operation_mode = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.reset_counter = 0x01;
  CRM.bit_access_auto.output_address_mode = 0x00;
  CRM.bit_access_auto.enable_programming =0x01;
  
#elif(MULTIPLEXING_MODE = AUTO2_MODE)
  CRM.bit_access_auto.mode = AUTO2_MODE;
  CRM.bit_access_auto.operation_mode = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.reset_counter = 0x01;
  CRM.bit_access_auto.output_address_mode = 0x00;
  CRM.bit_access_auto.enable_programming =0x01;
#endif

  adcDevice.setFunctionalMode(CRM);
}

void loop() {

  delay(300);
  Serial.println(adcDevice.readData(0x00));
  delay(300);
  Serial.println(adcDevice.readData(0x01));
  delay(300);
  Serial.println(adcDevice.readData(0x02));


  CRM.bit_access_auto.mode = AUTO1_MODE;
  CRM.bit_access_auto.operation_mode = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.reset_counter = 0x01;
  CRM.bit_access_auto.output_address_mode = 0x00;
  CRM.bit_access_auto.enable_programming =0x01;

  adcDevice.setFunctionalMode(CRM);

  delay(300);
  Serial.println(adcDevice.readData(NEXT_CHANNEL_AUTO_MODE));
  delay(300);
  Serial.println(adcDevice.readData(NEXT_CHANNEL_AUTO_MODE));
  delay(300);
  Serial.println(adcDevice.readData(NEXT_CHANNEL_AUTO_MODE));

}

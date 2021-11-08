
#include "ADS795X.h"

#include "SPI.h"

ADS795X adcDevice;

controlRegisterMode CRM;

void setup() {
  // put your setup code here, to run once:
  adcDevice.slave_select_pin = 0x07;
  adcDevice.auto1_active_channels = 0x07;
  adcDevice.initCommunication(SPI, 1, MSBFIRST, 1);
  
  CRM.bit_access_manual.mode = MANUAL_MODE;
  CRM.bit_access_manual.enable_programming = 0x01;
  CRM.bit_access_manual.next_channel = 0x00;
  CRM.bit_access_manual.input_range = 0x01;
  CRM.bit_access_manual.operation_mode = 0x00;
  CRM.bit_access_manual.output_address_mode = 0x00;
  
  adcDevice.setFunctionalMode(CRM);
}

void loop() {

  delay(10);
  adcDevice.readData(0x00);
  delay(10);
  adcDevice.readData(0x01);
  delay(10);
  adcDevice.readData(0x02);

}


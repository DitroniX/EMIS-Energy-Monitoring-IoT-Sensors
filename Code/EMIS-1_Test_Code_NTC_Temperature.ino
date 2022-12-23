/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32 GTIL RS232 RS485 MODBUS RELAY EEPROM OPTO CT Clamp Current Voltage
  PCA v1.00 - Test Code Firmware v1 - 27nd September 2022

  Simplified Board Bring Up Test - NTC Temperature (Output sent to Serial Print)
  .
  Remember!
  - Set the BOARD to ESP32 DEV Module (or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  .
  Note that in the default state, upon first power up and during reset, the Green LED will be partially lit. Once programmed and the GPIO defined, the Green LED will go off after power up.
  .
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  .
  This test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

// Libraries
#include <driver/adc.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED

// **************** INPUTS ****************
#define NTC_IN 39 //GPIO 39/VN (Analog ADC 1 CH3)

void setup() {

  // Stabalise
  delay(250);

  // Initialise UART:
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial);
  Serial.println("");

  // LEDs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);

}

void loop() {

  int Vo;
  float R1 = 10000;
  float logR2, R2, T, Tc, Tf;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  
  Vo = analogRead(NTC_IN);
  R2 = R1 * (4095.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 3.3 + 32.0;

  Serial.print("Temperature\t");
  Serial.print(Tf);
  Serial.print(" ºF\t");
  Serial.print(Tc);
  Serial.println(" ºC");

  // Heatbeat LED
  digitalWrite(LED_Red, LOW);
  delay(50);
  digitalWrite(LED_Red, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);

}

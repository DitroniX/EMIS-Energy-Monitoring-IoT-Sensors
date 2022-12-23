/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32 GTIL RS232 RS485 MODBUS RELAY EEPROM OPTO CT Clamp Current Voltage
  PCA v1.00 - Test Code Firmware v1 - 2nd September 2022

  Simplified Board Bring Up Test - Relay (Flash RED LED at same time)

  Remember!
      Set the BOARD to ESP32 DEV Module (or similar).
      You can also set the BAUD rate to 921600 to speed up flashing.
      The SDK does NOT need external power to flash.  It will take Power from the USB 5V.

  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.

  This test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED
#define Relay 12 // Relay

void setup() {

  // Stabalise
  delay(250);

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(Relay, OUTPUT);

  // LED Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);

  // Relay Default Off State
  digitalWrite(Relay, LOW);
}

void loop() {

  // Red
  digitalWrite(LED_Red, LOW);

  // Relay
  digitalWrite(Relay, HIGH);
  
  // Loop Delay
  delay(LoopDelay * 1000);

  // Off
  digitalWrite(LED_Red, HIGH);
  digitalWrite(Relay, LOW);
  
  // Loop Delay
  delay(LoopDelay * 1000);

}

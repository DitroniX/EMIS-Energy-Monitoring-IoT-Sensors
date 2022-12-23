/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32 GTIL RS232 RS485 MODBUS RELAY EEPROM OPTO CT Clamp Current Voltage
  PCA v1.00 - Test Code Firmware v1 - 2nd September 2022
  .
  Simplified Board Bring Up Test - RGB LED
  .
  Remember!
  - Set the BOARD to ESP32 DEV Module (or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  .
  Note that in the default state, upon first power up and during reset, the Green LED will be partially lit.  Once programmed and the GPIO defined, the Green LED will go off after power up.
  .
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  .
  This test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED
#define LED_Blue 15 // Blue LED

void setup() {

  // Stabalise
  delay(250);

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, HIGH);
}

void loop() {

  // Test RGB LEDs

  // Red
  digitalWrite(LED_Red, LOW);
  delay(1000);
  digitalWrite(LED_Red, HIGH);
  delay(100);

  // Green
  digitalWrite(LED_Green, LOW);
  delay(1000);
  digitalWrite(LED_Green, HIGH);
  delay(100);

  // Blue
  digitalWrite(LED_Blue, LOW);
  delay(1000);
  digitalWrite(LED_Blue, HIGH);
  delay(100);

  // White
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  delay(1000);
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, HIGH);
  delay(100);

}

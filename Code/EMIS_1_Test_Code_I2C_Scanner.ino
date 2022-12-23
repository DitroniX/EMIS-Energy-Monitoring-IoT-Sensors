/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32 GTIL RS232 RS485 MODBUS RELAY EEPROM OPTO CT Clamp Current Voltage
  PCA v1.00 - Test Code Firmware v1 - 27th September 2022

  Simplified Board Bring Up Test - I2C Bus Scanner (Output sent to the Serial Print)
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
#include <Wire.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED

// Define I2C (Expansion Port)
#define I2C_SDA 21
#define I2C_SCL 22

void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial);
  Serial.println("");

  // Initialize I2C 
  Wire.begin (I2C_SDA, I2C_SCL);

  // LEDs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);
}

void loop() {
  
  byte error, address;
  int nDevices;
  
  Serial.println("Scanning I2C Bus for Devices ...");
  
  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("Done\n");
  }

  // Heatbeat LED
  digitalWrite(LED_Red, LOW);
  delay(50);
  digitalWrite(LED_Red, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);
}

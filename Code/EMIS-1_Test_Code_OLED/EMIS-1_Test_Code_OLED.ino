/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32, LDO5V, LDO3V3, GTIL, RS232, RS485, MODBUS, RELAY, EEPROM, OPTO, CT Clamp, Current, Voltage, NTC, D1 Flashing Compatible
  PCA 1.2210-104 - Test Code Firmware v1 - 27th September 2022

  Simplified Board Bring Up Test - OLED Display via I2c (Heatbeat LED)

  Remember!
  - Set the BOARD to ESP32, 'WEMOS D1 MINI ESP32' DEV Module (or similar).
  - You may set the BAUD rate to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  Note: In the default state, upon first power up and during reset, the Green LED may be partially lit. Once programmed and the GPIO defined, the Green LED will go off after power up.

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and github.com/DitroniX
*/

// Libraries
#include <GyverOLED.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// Variables
float TestCount = 0;

// OLED Instance. You will need to select your OLED Display. 
// Uncomment/Comment as needed.
GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSH1106_128x64> oled;

// Draw Battery
void drawBattery(byte percent) {
  oled.drawByte(0b00111100);
  oled.drawByte(0b00111100);
  oled.drawByte(0b11111111);
  for (byte i = 0; i < 100 / 8; i++) {
    if (i < (100 - percent) / 8) oled.drawByte(0b10000001);
    else oled.drawByte(0b11111111);
  }
  oled.drawByte(0b11111111);
}

void setup() {

  // Stabalise
  delay(250);

  // LED
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  // LED Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(18, 0);
  oled.setScale(5);
  oled.print("EMIS");
  oled.update();
  delay(2000);
}

void loop() {

  // Test Counter.  Any random decimal number between 0 and 99
  TestCount = random(0, 9999);
  TestCount = TestCount / 100;

  // Update the display
  oled.clear();
  oled.setScale(3);
  oled.setCursor(0, 0);
  oled.print(TestCount);
  oled.println(" W");
  drawBattery(TestCount);
  oled.update();

  // Heatbeat LED
  digitalWrite(LED_Red, LOW);
  delay(50);
  digitalWrite(LED_Red, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);

}

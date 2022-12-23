/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 ESP32 GTIL RS232 RS485 MODBUS Current Voltage Energy Monitor 1.0
  PCA v1.00 - Test Code Firmware v1 - 28th September 2022

  Simplified Board Bring Up Test - CT Clamp Input with OLED Display Example

  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.

  This test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

// Libraries
#include <EmonLib.h>
#include <driver/adc.h>
#include <GyverOLED.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// Variables
float Sensor1 = 0;
float Sensor2 = 0;
double Irms;

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED

// **************** INPUTS ****************
#define CT_IN 35 // GPIO 35 (Analog ADC 1 CH7)

// Force EmonLib to use 1bit ADC resolution
#define ADC_BITS    12
#define ADC_COUNTS  (1<<ADC_BITS)
#define HOME_VOLTAGE 249.0
#define emonTxV3  // Force the library to use 3v3 as supply voltage

// EnergyMonitor Instance.
EnergyMonitor emon1;

// OLED Instance.
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
GyverOLED<SSH1106_128x64> oled;

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

  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
  analogReadResolution(ADC_BITS);

  // Initialize emon library (30 = ballpark calibration number - tweak for each board)
  emon1.current(CT_IN, 23.14);

  // OLED
  oled.init();
  oled.clear();
}

void loop() {

  double amps = emon1.calcIrms(5588); // Calculate Irms only.  Update Value as required.
  int watt = amps * HOME_VOLTAGE;

  if (amps > 0.15) { // Filter out the noise

    // Update the display
    Serial.print(watt);
    Serial.print(" W ");
    Serial.print(amps);
    Serial.println(" A");

    Serial.println("\n- - - - - - - - - - - - - - - - - - - -");

  }

  oled.clear();
  oled.setScale(3);
  oled.setCursor(0, 0);
  oled.print(watt);
  oled.println(" W");
  drawBattery(watt / 10);
  oled.update();

  // Heatbeat LEDs
  digitalWrite(LED_Red, LOW);
  delay(200);
  digitalWrite(LED_Red, HIGH);
  delay(200);

  // Loop Delay
  delay(LoopDelay * 100);

}

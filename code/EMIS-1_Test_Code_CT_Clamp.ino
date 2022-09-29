/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32 GTIL RS232 RS485 MODBUS RELAY EEPROM OPTO CT Clamp Current Voltage
  PCA v1.00 - Test Code Firmware v1 - 27th September 2022

  Simplified Board Bring Up Test - CT Clamp (Output sent to Serial Print)
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
#include <EmonLib.h>
#include <driver/adc.h>

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
#define CT_IN 35 //GPIO 35 (Analog ADC 1 CH7)

// Force EmonLib to use 1bit ADC resolution
#define ADC_BITS    12
#define ADC_COUNTS  (1<<ADC_BITS)
#define HOME_VOLTAGE 249.0
#define emonTxV3  //Force the library to use 3v3 as supply voltage

// EnergyMonitor Instance.
EnergyMonitor emon1;

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

  // Initialize emon library (30 = calibration number)
  emon1.current(CT_IN, 23.14);
}

void loop() {

  double amps = emon1.calcIrms(5588); // Calculate Irms only. Update Value as required.
  double watt = amps * HOME_VOLTAGE;

  if (amps > 0.15) { // Filter out the noise

    // Update the display
    Serial.print((int)watt);
    Serial.print(" W ");
    Serial.print(amps);
    Serial.println(" A");

    Serial.println("\n- - - - - - - - - - - - - - - - - - - -");

  }

  // Heatbeat LED
  digitalWrite(LED_Red, LOW);
  delay(50);
  digitalWrite(LED_Red, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);

}

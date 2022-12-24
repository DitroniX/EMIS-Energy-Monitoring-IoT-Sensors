/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  EMIS-1 Energy Monitoring IoT Sensors v1.0
  Features include ESP32, LDO5V, LDO3V3, GTIL, RS232, RS485, MODBUS, RELAY, EEPROM, OPTO, CT Clamp, Current, Voltage, NTC, D1 Flashing Compatible
  PCA 1.2210-104 - Test Code Firmware v1 - 28th September 2022

  Simplified Board Bring Up Test - DC Current Sensor Calibrate

  Remember!
  - Set the BOARD to ESP32, 'WEMOS D1 MINI ESP32' DEV Module (or similar).
  - You may set the BAUD rate to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  Note: In the default state, upon first power up and during reset, the Green LED may be partially lit. Once programmed and the GPIO defined, the Green LED will go off after power up.

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and github.com/DitroniX
*/


// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// Variables
float SensorRatioFactor = 0.0132;// ACS758-100B A 20mV/A is the factor @ 5V
//float SensorRatioFactor = 0.0238;// ACS758-50B 60mV/A is the factor @ 5V
float ADCFactorVoltage = 3.3 / 4095.0;  // 0.0008058
float SensorVoltage;
float SensorCalculatedCurrent;
float SensorZeroVoltage;

// **************** INPUTS ****************
#define CurrentSensor 34 //GPIO 34 (Analog ADC 1 CH6)

// **************** OUTPUTS ****************
#define LED_Red 2 // Red LED
#define LED_Green 4 // Green LED

void setup() {

  // Stabalise
  delay(250);

  // Initialise UART:
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial);
  Serial.println("");

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);

  // LED Default Off State
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Green, HIGH);

}

void loop() {

  // Test Procedure
  // 1 Run this code with 0A flowing.  
  // 2 Note 'Average SensorZeroVoltage' and update the SensorZeroVoltage variable below.  
  // 3 Retest under current.

  // Raw ADC Output
  Serial.print("ADC Raw: ");
  Serial.print(analogRead(CurrentSensor));

  // Calculating SensorZeroVoltage @  0A
  SensorZeroVoltage = ADCFactorVoltage * analogRead(CurrentSensor); // Read the voltage from sensor
  Serial.print("\tZero Current Voltage: ");
  Serial.print(SensorZeroVoltage);
  SensorZeroVoltage = 1.37; // Place Average Zero Voltage Here (from SensorZero @ 0A)

  // Calculate SensorVoltage Reading
  SensorVoltage = ADCFactorVoltage * analogRead(CurrentSensor);
  SensorVoltage = SensorVoltage - SensorZeroVoltage;
  Serial.print("\tV: ");
  Serial.print(SensorVoltage, 3);

  // Calculate Sensor Current Based on Calculation
  SensorCalculatedCurrent = SensorVoltage / SensorRatioFactor;
  Serial.print("\tI: ");
  Serial.print(SensorCalculatedCurrent, 2); Serial.println("A");

  // Heatbeat LED
  digitalWrite(LED_Red, LOW);
  delay(50);
  digitalWrite(LED_Red, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);
}

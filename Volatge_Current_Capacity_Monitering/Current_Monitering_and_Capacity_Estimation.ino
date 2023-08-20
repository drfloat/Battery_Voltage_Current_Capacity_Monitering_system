#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD library with pin numbers

const int voltagePin = A0; // Analog pin for voltage monitoring
const int currentPin = A1; // Analog pin for current monitoring
const float voltageDividerRatio = 3.3 / (3.3 + 10); // Voltage divider ratio
const float referenceVoltage = 5.0; // Arduino's reference voltage
const float shuntResistance = 0.1; // Shunt resistor value in ohms

unsigned long previousMillis = 0; // For time-based calculations
const unsigned long interval = 1000; // Interval for capacity estimation (1 second)

float accumulatedCurrent = 0; // Accumulated current over time
float batteryCapacity = 0; // Estimated battery capacity

void setup() {
  lcd.begin(16, 2); // Initialize the LCD
  lcd.print("Battery Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawVoltageValue = analogRead(voltagePin);
  int rawCurrentValue = analogRead(currentPin);

  // Convert ADC values to voltages
  float voltage = (rawVoltageValue * referenceVoltage) / 1023.0;
  float currentVoltage = (rawCurrentValue * referenceVoltage) / 1023.0;

  // Calculate battery voltage
  float batteryVoltage = voltage / voltageDividerRatio;

  // Calculate current using Ohm's law (V = IR)
  float current = currentVoltage / shuntResistance;

  // Calculate capacity over time
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Capacity = (Current * Time) / 3600 (convert millis to seconds)
    float currentSeconds = (float)interval / 1000.0;
    accumulatedCurrent += current * currentSeconds;
    batteryCapacity = accumulatedCurrent / 3600.0;
  }

  // Display values on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(batteryVoltage, 2);
  lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current, 2);
  lcd.print("A");

  delay(1000); // Delay between readings
}

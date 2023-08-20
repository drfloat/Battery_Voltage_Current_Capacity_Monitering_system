#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD library with pin numbers

const int voltagePin = A0; // Analog pin for voltage monitoring
const float voltageDividerRatio = 3.3 / (3.3 + 10); // Voltage divider ratio
const float referenceVoltage = 5.0; // Arduino's reference voltage

void setup() {
  lcd.begin(16, 2); // Initialize the LCD
  lcd.print("Battery Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read raw ADC value
  int rawValue = analogRead(voltagePin);

  // Convert ADC value to voltage
  float voltage = (rawValue * referenceVoltage) / 1023.0;

  // Calculate battery voltage
  float batteryVoltage = voltage / voltageDividerRatio;

  // Display battery voltage on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(batteryVoltage, 2);
  lcd.print("V");
  
  delay(1000); // Delay between readings
}

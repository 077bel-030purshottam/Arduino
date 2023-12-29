#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const int relayPin = 8;          // Connect relay to digital pin 8
const int zeroCrossPin = 2;      // Connect zero-crossing detector to digital pin 2
const int voltagePin = A0;       // Connect voltage sensor to analog pin A0
int current;
const int currentPin=A1;
const int ledPin = 13;           // LED for indication
const int correctionThreshold = 0.9;  // Adjust this threshold based on your requirements

volatile bool zeroCrossDetected = false;
float voltage;
float powerFactor;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(zeroCrossPin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(zeroCrossPin), zeroCrossing, RISING);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Power Factor:");
}

void loop() {
  if (zeroCrossDetected) {
    voltage = analogRead(voltagePin) * (5.0 / 1023.0);
    powerFactor = calculatePowerFactor();

    lcd.setCursor(0, 1);
    lcd.print("PF: ");
    lcd.print(powerFactor);

    if (powerFactor < correctionThreshold) {
      digitalWrite(relayPin, HIGH); // Turn on relay for power factor correction
      digitalWrite(ledPin, HIGH);   // Turn on LED for indication
    } else {
      digitalWrite(relayPin, LOW);  // Turn off relay
      digitalWrite(ledPin, LOW);    // Turn off LED
    }

    zeroCrossDetected = false;
  }
}

void zeroCrossing() {
  zeroCrossDetected = true;
}

float calculatePowerFactor() {
// Read voltage and current
  voltage = analogRead(voltagePin) * (5.0 / 1023.0);
  current = analogRead(currentPin) * (5.0 / 1023.0);

  // Calculate power factor
  powerFactor = calculatePowerFactor(voltage, current);

  // Display results on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage);
  lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current);
  lcd.print("A");

  lcd.setCursor(0, 2);
  lcd.print("Power Factor: ");
  lcd.print(powerFactor);

  delay(1000);  // Adjust the delay based on your requirements
}

float calculatePowerFactor(float voltage, float current) {
  // Calculate power factor using the cosine of the phase angle
  // This is a simplified example and may not be accurate for all loads
  float apparentPower = voltage * current;
  float realPower = voltage * current * powerFactor;
  
  if (apparentPower == 0) {
    return 0.0;  // Avoid division by zero
  } else {
    return realPower / apparentPower;
  }  return 1.0; 
}

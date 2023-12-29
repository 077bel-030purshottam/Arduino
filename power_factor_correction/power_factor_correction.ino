
const int outputPin = 13; // Choose a suitable output pin
// include the library code:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Current_read = 0;
int voltage_read = 0;
int output_current = 0;
int output_voltage = 0;
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //  lcd.print("hello, world!");
  lcd.print("Power factor correction");

  pinMode(outputPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.println("hi");

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  // Generate an approximate 11.1 MHz square wave using the tone function
  tone(outputPin, 11100);  // Use a frequency close to 11.1 MHz
  display_voltage();
  display_current();


}


void display_voltage() {

  //  int voltage_read = digitalRead(9);
  int voltage_read = analogRead(A0);
  delay(1000);
  Serial.println("Voltage is ");
  Serial.println(voltage_read);

  output_voltage = map(voltage_read, 0, 1023, 0, 255);
  analogWrite(9, output_voltage);
  Serial.println("Output voltage is ");
  Serial.println(output_voltage);

}

void display_current() {
  //  int Current_read = digitalRead(8);
  int Current_read = analogRead(A1);
  delay(1000);
  Serial.println("current is");
  Serial.println(Current_read);
  output_current = map(Current_read, 0, 1023, 0, 255);
  analogWrite(8, output_current);
  Serial.println("output current is ");
  Serial.println(output_current);


}

const int currentPin = A0;
int sensitivity = 185;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
 
void setup() 
{
  Serial.begin(9600);
}
 
void loop()
{
  adcValue = analogRead(currentPin);
  Serial.println("The input value is ");
  Serial.println(adcValue);
  adcVoltage = (adcValue / 1024.0) * 5000.0;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
 

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  
 
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);

  delay(2000);
 

}

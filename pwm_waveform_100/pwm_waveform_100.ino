#define _PWM_LOGLEVEL_       1

#include "AVR_PWM.h"
#define pinToUse     10    
#define LED_ON        LOW
#define LED_OFF       HIGH
AVR_PWM* PWM_Instance;

typedef struct
{
  uint16_t level;
} PWD_Data;

// Data for 1000Hz, PWMPeriod = 8000
PWD_Data PWM_data[] =
{
  {    0 },
  {  500 },
  { 1000 },
  { 1500 },
  { 2000 },
  { 2500 },
  { 3000 },
  { 3500 },
  { 4000 },
  { 4500 },
  { 5000 },
  { 5500 },
  { 6000 },
  { 6500 },
  { 7000 },
  { 7500 },
  { 8000 },
  { 7500 },
  { 7000 },
  { 6500 },
  { 6000 },
  { 5500 },
  { 5000 },
  { 4500 },
  { 4000 },
  { 3500 },
  { 3000 },
  { 2500 },
  { 2000 },
  { 1500 },
  { 1000 },
  {  500 },
  {    0 },
};

#define NUM_PWM_POINTS      ( sizeof(PWM_data) / sizeof(PWD_Data) )

float frequency;

// You can select any value
PWD_Data PWM_data_idle = PWM_data[0];

char dashLine[] = "============================================================================================";

void printPWMInfo(AVR_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle = ");
  Serial.print(PWM_Instance->getActualDutyCycle());
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->getPWMPeriod());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}




void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_Waveform on "));
  Serial.println(BOARD_NAME);
  Serial.println(AVR_PWM_VERSION);

  frequency = 30000.0f;

  // Create a dummy instance
  PWM_Instance = new AVR_PWM(pinToUse, frequency, 0);

  if (PWM_Instance)
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

    printPWMInfo(PWM_Instance);
  }
}
void updateDC()
{
  static uint16_t index = 0;

  // Mapping data to any other frequency from original data for 1000Hz, PWMPeriod = 8000
  PWM_Instance->setPWM_manual(pinToUse, ( ( (uint32_t) PWM_data[index].level * PWM_Instance->getPWMPeriod() ) / 8000) );

  // Use at low freq to check
  //printPWMInfo(PWM_Instance);

  index = (index + 1) % NUM_PWM_POINTS;
}
void check_status()
{
#define UPDATE_INTERVAL     50L

  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (100) milliseconds
  if (millis() > update_timeout)
  {
    updateDC();
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
check_status();
}

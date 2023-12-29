// Mega Code
// Uses A0 & A1 (PORT F)
#include "TimerOne.h"

#define period 50   // 50 Hz
#define LED 13      // Test output for analyser

byte index = 0;           // Index into sin table
boolean flipflop = true;  // Output pin toggle

uint8_t _sin[] = { // Calculated for 50Hz at 200 pulses per half wave.
  0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7,
  7, 8, 8, 8, 9, 9, 9,10,10,10,11,11,12,12,12,13,13,13,14,14,
  14,15,15,15,15,16,16,16,17,17,17,17,18,18,18,19,19,19,19,19,
  20,20,20,20,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,
  23,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,
  25,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,23,
  23,23,23,23,23,23,22,22,22,22,22,22,21,21,21,21,21,20,20,20,
  20,19,19,19,19,19,18,18,18,17,17,17,17,16,16,16,15,15,15,15,
  14,14,14,13,13,13,12,12,12,11,11,10,10,10, 9, 9, 9, 8, 8, 8,
  7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 1, 1, 1, 0, 0
};

void setup() {
  pinMode(LED,OUTPUT);
	// Pin mode, and set low.
	DDRF = DDRF | 0b00000011;   // Set as output
	PORTF = 0b00000000;         // Set low
	
	Timer1.initialize();
	Timer1.attachInterrupt(pwm,period);
}

void loop() {
}

void pwm() {
  if (flipflop){
    PORTF = 0b00000001;     //digitalWrite(A0,HIGH);
  } 
  else {
    PORTF = 0b00000010;     //digitalWrite(A1,HIGH);
  }
  
  byte duty_cycle = _sin[index++];
  if (duty_cycle > 3) {
    delayMicroseconds(duty_cycle);
  }
  
  PORTF = 0b00000000;       //digitalWrite(A0,LOW); & digitalWrite(A1,LOW);
  
  if (index > sizeof(_sin)) {
    index = 0;              // Reset index
    flipflop = !flipflop;   // Flip to other pin for next half cycle
    digitalWrite(LED,flipflop); // Test output used as analyser trigger
  }
}


// EXAMPLE USAGE

void setup() {
  pinMode(9, OUTPUT);     // sets the pin as output
}


void loop() {
  analogWriteResolution(9, 12); // sets analogWrite resolution to 12 bits
  analogWrite(9, 3000, 1000); // 3000/4095 = ~73% duty cycle at 1kHz
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {

  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
  delay(3000);

}

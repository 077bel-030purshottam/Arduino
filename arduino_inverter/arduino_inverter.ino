
#define pot A0
#define pwm 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot, INPUT);
  pinMode(pwm , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pot_value = analogRead(pot);
  Serial.println(pot_value);

  analogWrite(9, 64);
  delay(1000);
  analogWrite(9, 127);
  delay(1000);

  analogWrite(9, 191);
  delay(1000);

  analogWrite(9, 255);
  delay(1000);
  analogWrite(9, 0);
  delay(1000);



}

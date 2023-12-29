
int input_value = 0;
int  output_value = 0;



void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);



  // put your setup code here, to run once:

}

void loop() {



  // read potentionmeter reading
  input_value = analogRead(A0);
  Serial.println("The input value is ");
  Serial.println(input_value);

  output_value = map(input_value, 0, 1023, 0, 255);
  analogWrite(13, output_value);
  Serial.println("The output value is ");
  Serial.println(output_value);

  float voltage = output_value * 5.0 / 1023.0;
  Serial.println("The voltage of pin 13 is ");
  Serial.println(voltage);

  float voltage_value = input_value * 5.0 / 1023.0; // sensor value in voltage form
  Serial.println("The voltage value of the analog input ");
  Serial.println(voltage_value);
  digitalWrite(8, voltage_value);



  delay(1500);
  // put your main code here, to run repeatedly:

}

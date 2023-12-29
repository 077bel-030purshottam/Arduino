


int a = 1;
int b = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);

  // put your setup code here, to run once:
}

void loop() {

  if (a > b) {

    digitalWrite(9, HIGH);
    exit(0);
  }
}

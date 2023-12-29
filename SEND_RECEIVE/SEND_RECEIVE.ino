#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);// RX=9 and TX=10
void setup()
{
  mySerial.begin(9600);// Setting the baud rate of GSM Module
  Serial.begin(9600);// Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}

void loop()
{
  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        ReciveMessage();
        break;
    }
  if (mySerial.available() > 0)
    Serial.write(mySerial.read());
}
void ReciveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0");//recive SMS
  delay(1000);
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+9779803288790\"\r"); // Replace with mobile number
  delay(1000);
  mySerial.println("I am SMS, Subscribe!!!");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

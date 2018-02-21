int ledPin=13;
int buttonPin=7;
void setup()
{
pinMode(ledPin, OUTPUT);
 pinMode(buttonPin, INPUT);
 digitalWrite(buttonPin,HIGH);
}
void loop()
{
  int value=digitalRead(buttonPin);
  digitalWrite(ledPin, value);
}

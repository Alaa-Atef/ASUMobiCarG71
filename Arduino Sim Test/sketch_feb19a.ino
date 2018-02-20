int inputPins [] = {10,11,12,13};
int ledPins [] = {0,1,2,3};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i<4; i++)
  {
    pinMode(ledPins[i] , OUTPUT);
    pinMode(inputPins[i] , INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i<4; i++)
  {
    int value = digitalRead(inputPins[i]);
    digitalWrite (ledPins[i] , value);
  }

}

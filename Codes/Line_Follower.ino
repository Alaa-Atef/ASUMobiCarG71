//Motor Drive Connection
const int motorA  = 9;  //Right Motor
const int dirA1  = 6;
const int dirA2  = 7;

const int motorB  = 10; //Left Motor
const int dirB1  = 11;
const int dirB2  = 12;

//Bluetooth (HC-05)
const int BTState = 2;

//Useful Variables
int i = 0;
int j = 0;
int state;
int vSpeed = 255;   // Default speed, from 0 to 255

//Line Follower
int val1 = 0;    //center
const int sen1 = 8;
int val2 = 0;   //rght
const int sen2 = 4;
int val3 = 0;  //left
const int sen3 = 13;

void setup() {
  // Set pins as outputs:
  pinMode(motorA, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);

  pinMode(BTState, INPUT);

  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);

  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  pinMode(sen3, INPUT);


  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {

  /************************Line follower*****************************/
  val1 = digitalRead(sen1); //Center
  val2 = digitalRead(sen2); //Right
  val3 = digitalRead(sen3); //Left
  vSpeed = 180;

  if (val1 == 0 && val2 != 0 && val3 != 0) {
    Forward();
    Serial.print("F");
  }
  else if (val1 == 0 && val2 == 0 && val3 != 0) {

    RotateRight();
    Serial.print("R");
  }
  else if (val1 == 0 && val2 != 0 && val3 == 0) {

    RotateLeft();
    Serial.print("L");
  }
  else if (val1 == 0 && val2 == 0 && val3 == 0) {
    Forward();
    Serial.print("F");
  }
  else if (val2 == 0 && val1 != 0 && val3 != 0) {

    RotateRight();
    Serial.print("R");
  }
  else if (val3 == 0 && val1 != 0 && val2 != 0) {

    RotateLeft();
    Serial.print("L");
  }
}


void Forward()
{
  digitalWrite(dirA1, HIGH);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, HIGH);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, vSpeed);
}

void Backward()
{
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, HIGH);
  digitalWrite(dirB1, HIGH);
  digitalWrite(dirB2, LOW);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, vSpeed);
}

void Left()
{
  digitalWrite(dirA1, HIGH);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, LOW);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, 0);
}

void Right()
{
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, HIGH);
  analogWrite(motorA, 0);
  analogWrite(motorB, vSpeed);
}

void Stop()
{
  analogWrite(motorA, 0);
  analogWrite(motorB, 0);
}

void RotateRight()
{
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, HIGH);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, HIGH);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, vSpeed);
}

void RotateLeft()
{
  digitalWrite(dirA1, HIGH);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, HIGH);
  digitalWrite(dirB2, LOW);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, vSpeed);
}

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
float i = 0;
float j = 0;
float m = 0;
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

  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  pinMode(sen3, INPUT);

  pinMode(BTState, INPUT);
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  //Stop car when connection lost or bluetooth disconnected
  if (digitalRead(BTState) == LOW) {
    state = 'S';
  }

  //Save income data to variable 'state'
  if (Serial.available() > 0) {
    state = Serial.read();
    switch (state) {
      case'f': i = Serial.readString().toFloat(); break;
      case'b': j = Serial.readString().toFloat(); break;
      case'a': m = Serial.readString().toFloat(); break;
    }
  }

  //Change speed if state is equal from 0 to 4. Values must be from 0 to 255 (PWM)
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '1') {
    vSpeed = 100;
  }
  else if (state == '2') {
    vSpeed = 180;
  }
  else if (state == '3') {
    vSpeed = 200;
  }
  else if (state == '4') {
    vSpeed = 255;
  }

  if (state == 'f')
  {
    vSpeed = 255;
    Forward2();
    delay((i * 420) / 35);
    Stop();
    while (1)
    {
      delay(100);
      if (Serial.available() > 0) {
        break;
      }
    }

  }
  else if (state == 'b')
  {
    vSpeed = 255;
    Backward2();
    delay((j * 420) / 35);
    Stop();
    while (1)
    {
      delay(100);
      if (Serial.available() > 0) {
        break;
      }
    }
  }

  else if (state == 'a')
  {
    vSpeed = 255;
    RotateRight();
    delay((m * 462.5) / 135);
    Stop();
    while (1)
    {
      delay(100);
      if (Serial.available() > 0) {
        break;
      }
    }
  }

  //Circle
  else if (state == 'c')
  {
    vSpeed = 255;
    RotateRight2();
    delay(11500);
    Stop();
    while (1)
    {
      delay(100);
      if (Serial.available() > 0) {
        break;
      }
    }
  }

  //Rectangle
  else if (state == 'r')
  {
    vSpeed = 255;
    for (int k = 0 ; k < 4 ; k++)
    {
      Forward2();
      delay(2500);
      Stop();
      delay(500);
      RotateRight();
      delay((90 * 462.5) / 135);
      Stop();
      delay(500);
    }
    while (1)
    {
      delay(100);
      if (Serial.available() > 0) {
        break;
      }
    }
  }
  /************************Line follower*****************************/
  else if (state == 'W')
  {
    while (1)
    {

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

      //Save income data to variable 'state'
      if (Serial.available() > 0) {
        state = Serial.read();
      }
      if (state == 'w')
      {
        break;
      }
    }

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

void Forward2()
{
  digitalWrite(dirA1, HIGH);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, HIGH);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, 0.6 * vSpeed);
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

void Backward2()
{
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, HIGH);
  digitalWrite(dirB1, HIGH);
  digitalWrite(dirB2, LOW);
  analogWrite(motorA, vSpeed);
  analogWrite(motorB, 0.6 * vSpeed);
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

void RotateRight2()
{
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, HIGH);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, HIGH);
  analogWrite(motorA, 0.1 * vSpeed);
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



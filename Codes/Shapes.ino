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

void setup() {
  delay(5000);
  // Set pins as outputs:
  pinMode(motorA, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);

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
  if (state == 'c')
  {
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

  else if (state == 'r')
  {
    for(int i =0 ; i<4 ; i++)
    {
      Forward();
      delay(2500);
      Stop();
      delay(500);
      RotateRight();
      delay((90*462.5)/135);
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

}

void Forward()
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
  analogWrite(motorA, 0.1* vSpeed);
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



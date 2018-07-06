//Motor Drive Connection
const int motorA  = 9;  //Right Motor
const int dirA1  = 6;
const int dirA2  = 7;

const int motorB  = 10; //Left Motor
const int dirB1  = 11;
const int dirB2  = 12;

// SONIC
#define echoPin 3 // Echo Pin
#define trigPin 5 // Trigger Pin

int maximumRange = 55; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);

  distance = duration/58.2;

  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
  if (state == 'F') {
    if ( distance > maximumRange ) {
      Forward();
    }
    Serial.println("F");
  }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
  else if (state == 'G') {
    analogWrite(dirA1, vSpeed);
    analogWrite(dirA2, 0);
    analogWrite(dirB1, 0);
    analogWrite(dirB2, vSpeed);

    analogWrite(motorA, vSpeed);
    analogWrite(motorB, vSpeed * 0.5);

    Serial.println("G");
  }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
  else if (state == 'I') {
    analogWrite(dirA1, vSpeed);
    analogWrite(dirA2, 0);
    analogWrite(dirB1, 0);
    analogWrite(dirB2, vSpeed);

    analogWrite(motorA, 0.5 * vSpeed);
    analogWrite(motorB, vSpeed);

    Serial.println("I");
  }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
  else if (state == 'B') {
    Backward();
    Serial.println("B");
  }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
  else if (state == 'H') {
    analogWrite(dirA1, 0);
    analogWrite(dirA2, vSpeed);
    analogWrite(dirB1, vSpeed);
    analogWrite(dirB2, 0);

    analogWrite(motorA, vSpeed);
    analogWrite(motorB, 0.5 * vSpeed);

    Serial.println("H");
  }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
  else if (state == 'J') {
    analogWrite(dirA1, 0);
    analogWrite(dirA2, vSpeed);
    analogWrite(dirB1, vSpeed);
    analogWrite(dirB2, 0);

    analogWrite(motorA, 0.5 * vSpeed);
    analogWrite(motorB, vSpeed);

    Serial.println("J");
  }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
  else if (state == 'L') {
    Left();
    Serial.println("L");
  }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
  else if (state == 'R') {
    Right();
    Serial.println("R");
  }
  /***************************RotateLeft*****************************/
  else if (state == 'P') {
    RotateLeft();
    Serial.println("P");
  }
  /***************************RotateRight*****************************/
  else if (state == 'K') {
    RotateRight();
    Serial.println("K");
  }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
  else if (state == 'S') {
    Stop();
    Serial.println("S");
  }
  /************************Ultrasonic*****************************/
  if ( distance < maximumRange ) {
    Stop();
  }
  /************************Line follower*****************************/
  else if (state == 'W')
  {
    while(1)
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
    if(state=='w')
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



/*
   Created by Vasilakis Michalis // 12-12-2014 ver.1
   Project: Control RC Car via Bluetooth with Android Smartphone
   http://www.ardumotive.com/arduino-car
   More information at www.ardumotive.com
*/
//L293 Connection
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

//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
const int BTState = 2;

//Useful Variables
int i = 0;
int j = 0;
int state;
int vSpeed = 255;   // Default speed, from 0 to 255

void setup() {
  // Set pins as outputs:
  pinMode(motorA, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);

  pinMode(BTState, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


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

  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
  if (state == 'F') {
    digitalWrite(dirA1, HIGH);
    digitalWrite(dirA2, LOW);
    digitalWrite(dirB1, LOW);
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, vSpeed);
    analogWrite(motorB, vSpeed);
  }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
  else if (state == 'G') {
    digitalWrite(dirA1, HIGH);
    digitalWrite(dirA2, LOW);
    digitalWrite(dirB1, LOW);
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, vSpeed);
    analogWrite(motorB, vSpeed * .5);
  }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
  else if (state == 'I') {
    digitalWrite(dirA1, LOW);
    digitalWrite(dirA2, HIGH);
    digitalWrite(dirB1, LOW );
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, 0.5 * vSpeed);
    analogWrite(motorB, vSpeed);
  }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
  else if (state == 'B') {
    digitalWrite(dirA1, LOW);
    digitalWrite(dirA2, HIGH);
    digitalWrite(dirB1, HIGH);
    digitalWrite(dirB2, LOW);
    analogWrite(motorA, vSpeed);
    analogWrite(motorB, vSpeed);
  }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
  else if (state == 'H') {
    digitalWrite(dirA1, LOW);
    digitalWrite(dirA2, HIGH);
    digitalWrite(dirB1, HIGH);
    digitalWrite(dirB2, LOW);
    analogWrite(motorA, vSpeed);
    analogWrite(motorB, 0.5 * vSpeed);
  }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
  else if (state == 'J') {
    digitalWrite(dirA1, LOW);
    digitalWrite(dirA2, HIGH);
    digitalWrite(dirB1, LOW);
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, 0.5 * vSpeed);
    analogWrite(motorB, vSpeed);
  }

  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
  else if (state == 'L') {
    digitalWrite(dirA1, HIGH);
    digitalWrite(dirA2, LOW);
    digitalWrite(dirB1, LOW);
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, vSpeed);
    analogWrite(motorB, 0);
  }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
  else if (state == 'R') {
    digitalWrite(dirA1, LOW);
    digitalWrite(dirA2, HIGH);
    digitalWrite(dirB1, LOW);
    digitalWrite(dirB2, HIGH);
    analogWrite(motorA, 0);
    analogWrite(motorB, vSpeed);
  }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
  else if (state == 'S') {
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
  }
  //SONIC
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  if ( distance < maximumRange || distance > minimumRange) {
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);

  }

}




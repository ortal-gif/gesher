#include <SoftwareSerial.h>

// PIN DEFFINITIONS
const int motorIN1 = 7;
const int motorIN2 = 6;
const int motorIN3 = 5;
const int motorIN4 = 4;
const int motorEN1 = 3;
const int motorEN2 = 9;

// Sensor pins
//const int trigPin = 12;
//const int echoPin = 11;
//const int ldrPin = A0;




void setup() {
  // Motor pins 
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  pinMode(motorEN1, OUTPUT);
  pinMode(motorEN2, OUTPUT);
}

void loop() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, HIGH);
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
  analogWrite(motorEN1, 80);
  analogWrite(motorEN2, 80);
  delay(1200);
  analogWrite(motorEN1, 0);
  analogWrite(motorEN2, 0);
  delay(2000);
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
  analogWrite(motorEN1, 80);
  analogWrite(motorEN2, 80);
  delay(1200);
  analogWrite(motorEN1, 0);
  analogWrite(motorEN2, 0);
  delay(2000);
}

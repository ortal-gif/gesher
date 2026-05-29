#include <SoftwareSerial.h>

// PIN DEFFINITIONS
const int motorIN1 = 7;
const int motorIN2 = 6;
const int motorIN3 = 5;
const int motorIN4 = 4;
const int motorEN1 = 3;
const int motorEN2 = 9;

// Sensor pins
const int trigPin = 12;
const int echoPin = 11;

const long STOP_DIST_CM = 10;


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
  long dist = readUltrasonicCM();

  Serial.print("  Dist: "); Serial.println(dist);
  
  if (dist > 0 && dist <= STOP_DIST_CM) {
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
    delay(2000);}
}

//---ULTRASONIC HELPER---
long readUltrasonicCM(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return duration / 29 / 2;
}

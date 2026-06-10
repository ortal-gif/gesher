#include <Servo.h>

// ---------- PINS ----------
const int SERVO_PIN = 2;

// Boat ultrasonic
const int BOAT_TRIG = 12;
const int BOAT_ECHO = 11;

// Motor driver
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int ENA = 3;
const int ENB = 9;

// LEDs and buzzer
const int GREEN_LED = 10;
const int RED_LED = 13;
const int BUZZER = A0;

// ---------- SETTINGS ----------
const int BOAT_DISTANCE = 25;

const int MOTOR_SPEED = 100;

const int BARRIER_OPEN = 90;
const int BARRIER_CLOSED = 0;

const unsigned long OPEN_TIME = 1500;
const unsigned long CLOSE_TIME = 1500;

Servo barrier;

void setup() {
  Serial.begin(9600);

  pinMode(BOAT_TRIG, OUTPUT);
  pinMode(BOAT_ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  barrier.attach(SERVO_PIN);

  stopMotor();
  normalMode();

  Serial.println("Drawbridge started");
}

void loop() {
  long boat = readUltrasonicCM(BOAT_TRIG, BOAT_ECHO);

  Serial.print("Boat: ");
  Serial.print(boat);
  Serial.println(" cm");

  if (boat > 0 && boat <= BOAT_DISTANCE) {
    boatDetectedSequence();
  }

  delay(300);
}

void boatDetectedSequence() {
  Serial.println("Boat detected!");

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  warningBeep();

  barrier.write(BARRIER_CLOSED);
  delay(1000);

  Serial.println("Opening bridge.");

  openBridge();
  delay(OPEN_TIME);
  stopMotor();

  while (true) {
    long boat = readUltrasonicCM(BOAT_TRIG, BOAT_ECHO);

    Serial.print("Waiting for boat to pass: ");
    Serial.println(boat);

    if (boat == -1 || boat > BOAT_DISTANCE) {
      break;
    }

    warningBeep();
    delay(500);
  }

  delay(1500);

  Serial.println("Closing bridge.");

  closeBridge();
  delay(CLOSE_TIME);
  stopMotor();

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  successBeep();
  normalMode();
}

void normalMode() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);

  barrier.write(BARRIER_OPEN);
}

long readUltrasonicCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration / 58;
}

void openBridge() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, MOTOR_SPEED + 20);
  digitalWrite(ENB, HIGH);
}

void closeBridge() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(ENB, HIGH);
}

void stopMotor() {
  analogWrite(ENA, 0);
  digitalWrite(ENB, LOW);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void warningBeep() {
  tone(BUZZER, 4000, 200);
}

void successBeep() {
  tone(BUZZER, 3500, 150);
  delay(200);
  tone(BUZZER, 3000, 150);
}

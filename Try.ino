#include <SoftwareSerial.h>
#include <NewPing.h>

// --- PIN DEFINITIONS ---
const int motorIN1 = 7;   // Motor 1 direction pin A
const int motorIN2 = 6;   // Motor 1 direction pin B
const int motorIN3 = 5;   // Motor 2 direction pin A
const int motorIN4 = 4;   // Motor 2 direction pin B
const int motorEN1 = 3;   // Motor 1 speed (PWM)
const int motorEN2 = 9;   // Motor 2 speed (PWM)

const int trigPin = 12;         // Ultrasonic sensor trigger pin
const int echoPin = 11;         // Ultrasonic sensor echo pin
const long STOP_DIST_CM = 10;   // Distance threshold in cm

// Create sonar object with trig pin, echo pin, and max distance of 200cm
NewPing sonar(trigPin, echoPin, 200);

void setup() {
  Serial.begin(9600); // Start serial monitor for debugging

  // Set all motor pins as outputs
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  pinMode(motorEN1, OUTPUT);
  pinMode(motorEN2, OUTPUT);
}

void loop() {
  delay(60); // Short delay to let the sensor settle between pings

  long dist = sonar.ping_cm(); // Read distance from ultrasonic sensor

  // If 0 is returned, the object is out of range or no echo was received
  if (dist == 0) {
    Serial.println("Out of range / no reading");
    return; // Skip the rest of the loop and try again
  }

  Serial.print("Dist: "); Serial.println(dist);

  // If something is detected within the threshold distance, trigger the motors
  if (dist <= STOP_DIST_CM) {

    // --- MOTORS UP ---
    // Set both motors to spin in the "up" direction
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, HIGH);
    digitalWrite(motorIN3, LOW);
    digitalWrite(motorIN4, HIGH);
    analogWrite(motorEN1, 80); // Set motor 1 speed
    analogWrite(motorEN2, 80); // Set motor 2 speed
    delay(1200);               // Run motors for 1.2 seconds

    // Stop both motors
    analogWrite(motorEN1, 0);
    analogWrite(motorEN2, 0);
    delay(2000); // Wait 2 seconds before going down

    // --- MOTORS DOWN ---
    // Set both motors to spin in the "down" direction
    digitalWrite(motorIN1, HIGH);
    digitalWrite(motorIN2, LOW);
    digitalWrite(motorIN3, HIGH);
    digitalWrite(motorIN4, LOW);
    analogWrite(motorEN1, 80); // Set motor 1 speed
    analogWrite(motorEN2, 80); // Set motor 2 speed
    delay(1200);               // Run motors for 1.2 seconds

    // Stop both motors
    analogWrite(motorEN1, 0);
    analogWrite(motorEN2, 0);
    delay(2000); // Wait 2 seconds before scanning again
  }
}

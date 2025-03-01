#include <Servo.h>

// ----- Motor Board 1 (L298N) -----
// Motor A (Board 1)
#define M1_IN1 46   // Direction control pin
#define M1_IN2 48   
// Motor B (Board 1)
#define M2_IN1 50   // Direction control pin
#define M2_IN2 52   

// ----- Motor Board 2 (L298N) -----
// Motor C (Board 2)
#define M3_IN1 5    // Direction control pin
#define M3_IN2 6    
// Motor D (Board 2)
#define M4_IN1 7    // Direction control pin
#define M4_IN2 8    

// ----- Servo control pins -----
// Servo 1 on digital pin 9
#define SERVO1_PIN 9
// Servo 2 on digital pin 10
#define SERVO2_PIN 10
// Servo 3 on digital pin 12 (corrected to match the comment)
#define SERVO3_PIN 12

Servo servo1;
Servo servo2;
Servo servo3;

int servoAngle = 0;       // Current angle for all servos
int servoIncrement = 1;   // Step size for servo movement
unsigned long previousMillis = 0;
const long servoInterval = 15;  // Update interval (ms)

void setup() {
    // Setup motor pins for Board 1
    pinMode(M1_IN1, OUTPUT);
    pinMode(M1_IN2, OUTPUT);
    pinMode(M2_IN1, OUTPUT);
    pinMode(M2_IN2, OUTPUT);
    
    // Setup motor pins for Board 2
    pinMode(M3_IN1, OUTPUT);
    pinMode(M3_IN2, OUTPUT);
    pinMode(M4_IN1, OUTPUT);
    pinMode(M4_IN2, OUTPUT);
    
    // Attach the three servos to their pins
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);
    servo3.attach(SERVO3_PIN);
    
    Serial.begin(115200);
}

void loop() {
    // Continuously drive the motors
    runMotors();
    
    // Non-blocking update for servo positions
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= servoInterval) {
        previousMillis = currentMillis;
        servo1.write(servoAngle);
        servo2.write(servoAngle);
        servo3.write(servoAngle);
        
        // Adjust the servo angle and reverse direction at endpoints
        servoAngle += servoIncrement;
        if (servoAngle <= 0 || servoAngle >= 180) {
            servoIncrement = -servoIncrement;
        }
    }
}

// Function to continuously set motor directions for both boards
void runMotors() {
    // ----- Motor Board 1 -----
    // Motor A: forward (set M1_IN1 HIGH, M1_IN2 LOW)
    digitalWrite(M1_IN1, HIGH);
    digitalWrite(M1_IN2, LOW);
    // Motor B: backward (set M2_IN1 LOW, M2_IN2 HIGH)
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);
    
    // ----- Motor Board 2 -----
    // Motor C: forward (set M3_IN1 HIGH, M3_IN2 LOW)
    digitalWrite(M3_IN1, HIGH);
    digitalWrite(M3_IN2, LOW);
    // Motor D: backward (set M4_IN1 LOW, M4_IN2 HIGH)
    digitalWrite(M4_IN1, LOW);
    digitalWrite(M4_IN2, HIGH);
}

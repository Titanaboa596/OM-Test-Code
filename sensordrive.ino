#include <Servo.h>

// ----- Motor Board 1 (L298N) -----
#define M1_IN1 46   // Motor A direction control pin
#define M1_IN2 48   
// Motor B (Board 1)
#define M2_IN1 50   // Motor B direction control pin
#define M2_IN2 52   

// ----- Motor Board 2 (L298N) -----
#define M3_IN1 5    // Motor C direction control pin
#define M3_IN2 6    
// Motor D (Board 2)
#define M4_IN1 7    // Motor D direction control pin
#define M4_IN2 8    

// ----- Ultrasonic sensor pins -----
const int trigPin = 11;
const int echoPin = 13;

// ----- Color sensor (GY-31/TCS3200) pins -----
int s1 = 22;
int s0 = 24;
int ledPin = 26;
int s2 = 28;
int s3 = 30;
int sensorOut = 32;

// Color sensor variables
long redFrequency = 0;
long greenFrequency = 0;
long blueFrequency = 0;

// Target color
String targetColor = "red"; // Set target color to detect

void setup() {
  // -------- Setup Motor Boards --------
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);
  pinMode(M4_IN1, OUTPUT);
  pinMode(M4_IN2, OUTPUT);
  
  // -------- Setup Ultrasonic Sensor --------
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // -------- Setup Color Sensor --------
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // Turn on LED for illumination
  digitalWrite(s0, HIGH);      // Set frequency scaling to 20%
  digitalWrite(s1, LOW);
  pinMode(sensorOut, INPUT);
  
  // -------- Initialize Serial Communication --------
  Serial.begin(115200);
}

void loop() {
  // Measure the frequencies of red, green, and blue
  readColorFrequencies();
  
  // Check if the target color (red) is detected
  if (targetColor == "red" && redFrequency < greenFrequency && redFrequency < blueFrequency) {
    Serial.println("Red color detected!");
    
    // Start the motors to run until the ultrasonic sensor detects a distance of less than 3 cm
    runMotors();
    
    // Keep checking the distance
    while (true) {
      int distance = measureDistance();
      Serial.print("Ultrasonic Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      // Stop the motors if the distance is less than 3 cm
      if (distance < 3) {
        stopMotors();
        Serial.println("Motors stopped, distance is less than 3 cm.");
        break; // Exit the loop and stop motors
      }
      delay(100); // Add a small delay to avoid flooding the serial monitor
    }
  } else {
    Serial.println("Target color not detected");
  }
  
  delay(500);  // Add a short delay to avoid flooding the serial monitor
}

// Function to read red, green, and blue frequencies
void readColorFrequencies() {
  // Measure red light frequency
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  
  // Measure blue light frequency
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Measure green light frequency
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Print the color sensor readings to the Serial Monitor
  Serial.print("Color Sensor -> Red: ");
  Serial.print(redFrequency);
  Serial.print("  Blue: ");
  Serial.print(blueFrequency);
  Serial.print("  Green: ");
  Serial.println(greenFrequency);
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to run the motors
void runMotors() {
  // Motor Board 1 (Motor A and Motor B)
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW); // Motor A moves forward
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, HIGH); // Motor B moves backward
  
  // Motor Board 2 (Motor C and Motor D)
  digitalWrite(M3_IN1, HIGH);
  digitalWrite(M3_IN2, LOW); // Motor C moves forward
  digitalWrite(M4_IN1, LOW);
  digitalWrite(M4_IN2, HIGH); // Motor D moves backward
}

// Function to stop the motors
void stopMotors() {
  // Stop Motor Board 1
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
  
  // Stop Motor Board 2
  digitalWrite(M3_IN1, LOW);
  digitalWrite(M3_IN2, LOW);
  digitalWrite(M4_IN1, LOW);
  digitalWrite(M4_IN2, LOW);
}

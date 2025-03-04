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
    measureDistance();  // Measure the distance when red is detected
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
void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  // Print the measured distance
  Serial.print("Red color detected. Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}


// Define motor control pins
#define ENA 9   // Motor A speed control (PWM)
#define IN1 5   // Motor A direction 1
#define IN2 6   // Motor A direction 2
#define ENB 10  // Motor B speed control (PWM)
#define IN3 7   // Motor B direction 1
#define IN4 8   // Motor B direction 2

void setup() {
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    Serial.begin(115200);
    stopMotors();
}

void loop() {
    int speedValue = 150; // Adjust speed (0-255)

    Serial.print("Setting Speed: ");
    Serial.println(speedValue);

    // One motor forward, one motor backward
    moveOppositeDirections(speedValue);
    delay(3000);

    // Stop
    stopMotors();
    delay(1000);
}

// Function to move Motor A forward & Motor B backward
void moveOppositeDirections(int speed) {
    digitalWrite(IN1, HIGH); // Motor A Forward
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, LOW);  // Motor B Backward
    digitalWrite(IN4, HIGH);

    analogWrite(ENA, constrain(speed, 0, 255));
    analogWrite(ENB, constrain(speed, 0, 255));
}

// Function to stop both motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}
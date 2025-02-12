// Motor driver pins
#define ENA 9
#define ENB 10
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  forward();  
  delay(2000);

  backward();
  delay(2000);

  turnLeft();
  delay(1500);

  turnRight();
  delay(1500);

  stopMotors();
  delay(2000);
}

// Move forward
void forward() {
  analogWrite(ENA, 150);  // Speed control
  analogWrite(ENB, 150);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move backward
void backward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn left
void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turn right
void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

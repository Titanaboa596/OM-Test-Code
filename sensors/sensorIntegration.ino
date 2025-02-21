// Define pins for TCS3200 Color Sensor
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT 8

// Define pins for Ultrasonic Sensor
#define TRIG 9
#define ECHO 10

// Set target color (options: "red", "green", "blue")
String targetColor = "red";

void setup() {
    Serial.begin(9600);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    
    // Set frequency scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
}

// Function to read color frequency
int readColor(int s2, int s3) {
    digitalWrite(S2, s2);
    digitalWrite(S3, s3);
    delay(100);
    return pulseIn(OUT, LOW);
}

void getColor() {
    int red = readColor(LOW, LOW);
    int green = readColor(HIGH, HIGH);
    int blue = readColor(LOW, HIGH);
    
    Serial.print("Red: "); Serial.print(red);
    Serial.print(" Green: "); Serial.print(green);
    Serial.print(" Blue: "); Serial.println(blue);
    
    if (targetColor == "red" && red < green && red < blue) {
        measureDistance();
    } else if (targetColor == "green" && green < red && green < blue) {
        measureDistance();
    } else if (targetColor == "blue" && blue < red && blue < green) {
        measureDistance();
    } else {
        Serial.println("Target color not detected");
    }
}

// Function to measure distance using ultrasonic sensor
void measureDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    
    long duration = pulseIn(ECHO, HIGH);
    int distance = duration * 0.034 / 2;
    
    Serial.print("Locked on target. Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

void loop() {
    getColor();
    delay(500);
}

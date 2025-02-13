#define TRIG_PIN 9
#define ECHO_PIN 8;


long distance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  long distance = (duration *0.034)/2;
  return distance;
}

void avoidObstacle() {
    if (distance() < 10) {  // 10cm
        stopMotors();
    }
}

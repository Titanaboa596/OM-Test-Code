int trig = 9;
int echo = 8;
int distance = 0;
long duration =0;
void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
 
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration *0.034)/2;
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
   
}

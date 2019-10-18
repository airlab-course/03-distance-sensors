const int echoPin = 8;
const int trigPin = 9;

void setup()
{
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  Serial.begin(115200);
}

void loop() {
  float result = readDist();
  Serial.println(result);
  delay(150);
}

float readDist(){
  // speed of sound is 340 meters per second
  // sound traverses twice
  // time is measured in microseconds
  // distance is measured in centimeters
  return readPulse() * (340.0 * 100.0) / (2.0 * 1000.0 * 1000.0);    
}

float readPulse()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration;
}


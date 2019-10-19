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

float readDist()
{
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readPulse() * speedOfSoundCmPerUs / 2.0;    
}

float readPulse()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration;
}

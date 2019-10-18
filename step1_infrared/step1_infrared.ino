const int sensorPin = A0;

void setup()
{
  Serial.begin(115200);
}

void loop() {
  delay(100);
  int result = analogRead(sensorPin);
  Serial.println(result);
}

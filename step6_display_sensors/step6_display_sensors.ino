#include <LedControl.h>

const int sensorPin = A0;
const float voltsPerMeasurement = 5.0/1024.0;

const int echoPin = 8;
const int trigPin = 9;

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);

int prevRow = 0;
int prevCol = 0;

void setup()
{
  Serial.begin(115200);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 16);
  lc.clearDisplay(0);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  float irDistance = readDistIR();
  irDistance = constrain(irDistance, 20, 120);
  int curRow = convertToPixel(irDistance);
  
  float usDistance = readDistUS();
  usDistance = constrain(usDistance, 20, 120);
  int curCol = convertToPixel(usDistance);
  
  lc.setLed(0, prevRow, prevCol, false);
  lc.setLed(0, curRow, curCol, true);
  prevRow = curRow;
  prevCol = curCol;


  Serial.print(irDistance);
  Serial.print(' ');
  Serial.print(usDistance);
  Serial.println();


  delay(150);
//  Serial.print(curRow);
//  Serial.print(' ');
//  Serial.print(curCol);
//  Serial.println();
}

int convertToPixel(float dist)
{
  float constrained = constrain(dist, 20, 120);
  return (int) constrain((constrained - 20) / 7, 0, 7);
}

float readDistUS(){
  // speed of sound is 340 meters per second
  // sound traverses twice
  // time is measured in microseconds
  // distance is measured in centimeters
  return readPulseUS() * (340.0 * 100.0) / (2.0 * 1000.0 * 1000.0);    
}

float readPulseUS()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 1000*1000*15);

  return duration;
}

float readDistIR(){
  float volts = readAnalogIR() * voltsPerMeasurement;
  return 65 * pow(volts, -1.10); // for big IR sensor (SHARP 2Y0A02)
  //return pow(14.7737/volts, 1.2134); // for small IR sensor (SHARP 2Y0A21)
}

float readAnalogIR()
{
  int sum = 0;
  int maxV = -5000;
  int minV = 5000;
  int n = 15;
  for (int i = 0; i < n; i++)
  {
    int cur = analogRead(sensorPin);
    if (cur > maxV)
    {
      maxV = cur;
    }
    if (cur < minV)
    {
      minV = cur;
    }
    sum += cur;
    delay(6);
  }
  return (sum - maxV - minV) / (float)(n - 2);
}
 

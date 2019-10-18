#include <Ultrasonic.h>
#include <LedControl.h>
//https://github.com/wayoda/LedControl/blob/master/src/LedControl.h

const int firePin = A0;

const int echoPinMove = 8;
const int trigPinMove = 9;
Ultrasonic ultrasonicMove(trigPinMove, echoPinMove);

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 11;
const int csPin = 10;

float averageMove = 0.0;
float averageFire = 0.0;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount); // Pin and # of Displays

int gunX = 0;

byte bullets[8] = {8, 8, 8, 8, 8, 8, 8, 8};
void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);

  Serial.begin(9600);
}



void drawGun(int x) {
  lc.setRow(0, 0, B111 << x);
  lc.setRow(0, 1, B010 << x);
}
void moveGun() {
  int dist = 0.4 * averageMove + 0.6 * ultrasonicMove.distanceRead();
  averageMove = dist;
  
  Serial.println(dist);
  if (dist == 0 || dist > 40)
    return;

  gunX = dist / 5;
  gunX = min(max(gunX, 0), 5);
  drawGun(gunX);
}

void moveBullet(int x) {
  if (bullets[x] > 8)
    return;

  //Точка усложнения - одноверменный полет нескольких пуль setColumn + побитовый сдвиг.
  lc.setLed(0, bullets[x], x, false);
  bullets[x]++;
  lc.setLed(0, bullets[x], x, true);
}

void moveAllBullets() {
  for (int x = 0; x < 8; x++) {
    moveBullet(x);
  }
}
void fireNewBullet() {
  int dist = 0.5 * averageFire + 0.5 * readDist(firePin);
  averageFire = dist;
  //Serial.println(dist);
  if (dist >= 30)
    return;

  lc.setLed(0, bullets[8 - gunX - 2], gunX, false);
  bullets[8 - gunX - 2] = 2;
}


void loop() {
  delay(500);
  moveGun();
  fireNewBullet();
  moveAllBullets();

}


const float voltsPerMeasurement = 5.0/1024.0;
float readDist(int pin){
  float volts = analogRead(pin)*voltsPerMeasurement;
  return 65*pow(volts, -1.10);    
}

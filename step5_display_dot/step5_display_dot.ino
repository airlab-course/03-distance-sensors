#include <LedControl.h>

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 16);
  lc.clearDisplay(0);
}

void loop() {
  lc.setLed(0, 3, 3, true);
  delay(500);
  lc.setLed(0, 3, 3, false);
  delay(500);
}


// test addition

#include <Adafruit_NeoPixel.h>

#define stripLength 2
#define PIN 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(stripLength, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
}

void loop()
{
  strip.setPixelColor(0, 0, 0xFF, 0);
  strip.setPixelColor(1, 0xFF, 0, 0);
  strip.show();
  delay(1000);
}

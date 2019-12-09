//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Effects.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2
int NUMPIXELS = 7;

Effects jewel = Effects(NUMPIXELS, PixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  jewel.begin();
  jewel.setBrightness(200);
  jewel.rainbowCycle(10);

  jewel.show();
}

void loop() {

  jewel.Update();
  
}

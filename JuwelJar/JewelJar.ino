//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define JuwelPin D2
#define ProgramPin D8
#define LEDPin D6
#define BrightPin A0

int NUMPIXELS = 2;

int MaxBright = 10;
int MinBright = 1;

int MaxVolt = 1024;
int MinVolt = 0;

long Bright;
int BrightVolt;

int program = 1;

long lastDebounceTime = 0;
long debounceDelay = 50;
int currentPinState = LOW;
int previousPinState = LOW;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, JuwelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(ProgramPin,INPUT);
  pinMode(LEDPin,OUTPUT);
  pinMode(BrightPin,INPUT);

  BrightVolt = analogRead(BrightPin);
  Bright = map(BrightVolt, MinVolt, MaxVolt, MinBright, MaxBright);

  strip.setBrightness(Bright);
  rainbowCycle(20);
  strip.show();
  Serial.println("finished setup");
}

void loop() {
  //strip.Update();
  //Wert an Analogpin auslesen und auf Helligkeit zwischen Min und Max wert Mappen
  // dafür muss vorher maximale und minimale Spannung aber bekannt sein, die hier auftritt
  BrightVolt = analogRead(BrightPin);
  Bright = map(BrightVolt, MinVolt, MaxVolt, MinBright, MaxBright);

  strip.setBrightness(Bright);

  strip.setPixelColor(1,144,100,244);
  strip.setPixelColor(2,144,100,244);
  // Wenn Programmwahltaster betätigt wird, welchselt ProgramPin zu High,
  //*currentPinState = digitalRead(ProgramPin);
  //*if (currentPinState != previousPinState){
  //*  lastDebounceTime = millis();
  //*}
  //*if ((millis() - lastDebounceTime) > debounceDelay){
  //*  if (currentPinState == HIGH){
  //*    program = program +1;
  //*    selectProgram(program);
  //*  }
  //*}
  //*if (program >= 1){
  //*  program = 0;
  //*}
  strip.show();
  Serial.println("finished loop");
}

//nächstes Programm wählen und Programmwechsel mit Blinken der LED bestätigen
void selectProgram(int program) {
  for (int i=0; i<=NUMPIXELS; i++){
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(1);
  if (program == 1){
    rainbowCycle(20);
  }
  else if (program ==2){
     colorWipe(0x00,0xff,0x00, 50);
  }
    digitalWrite(LEDPin,HIGH);
    delay(500);
    digitalWrite(LEDPin,LOW);
    delay(500);
    digitalWrite(LEDPin,HIGH);
    delay(500);
    digitalWrite(LEDPin,LOW);
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      c=Wheel(((i * 256 / NUMPIXELS) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
  Serial.println("Rainbow");
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, red, green, blue);
      strip.show();
      delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
    

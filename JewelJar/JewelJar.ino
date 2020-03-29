//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Effects.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2
int NUMPIXELS = 7;

Effects jewel = Effects(NUMPIXELS, PixelPin, NEO_GRB + NEO_KHZ800);

#include <Homie.h>
HomieNode jewelNode("jeweljar", "jeweljar", "light");

//Definition of possible effects
char* effectList[] = {"fade", "rainbow", "heartbeat", "none"};
bool EffectChange;                        //variable indication change in effect (0=no change, 1=change), initially one change necessary 

uint32_t color;
String effect;

//Definition of Switch
#define PinSwitch D6
int intervalSwitch = 500; //interval in which no new Switch is allowed
int lastSwitch;

long MaxBrightness = 150;


void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  Homie_setFirmware("jeweljar", "1.0.0");
  jewelNode.advertise("effect").settable(effectHandler);
  jewelNode.advertise("color").settable(colorHandler);
  jewelNode.advertise("brightness").settable(brightnessHandler);
  Homie.setup();
  
  jewel.begin();
  jewel.setBrightness(150);

  jewel.show();

  color = jewel.Color(255,0,0); //initial definition of color
  effect = "none";              //initial definition of effect
}

void loop() {
  Homie.loop();
  jewel.Update();
  //if switch state is HIGH, Change Effect
  if (millis()-lastSwitch > intervalSwitch){
    if (digitalRead(PinSwitch) == HIGH){
      EffectChange = 1;
      effect = effectList[random(0,3)];
      color = jewel.Color(random(0,255),random(0,255),random(0,255));
      lastSwitch = millis();
      jewelNode.setProperty("effect").send(effect);
    }
  }
  
  //Change Effect or Color
  if (EffectChange == 1){
    EffectChange = 0;
    jewel.clear();
    //Initialization
    SelectEffect(effect);
  }
  //no Change: just update effect
  else{
    jewel.Update();
  }  
}

bool effectHandler(const HomieRange& range, const String& value){
  effect = value;
  EffectChange = 1;  
  jewelNode.setProperty("effect").send(value);     
}

bool colorHandler (const HomieRange& range, const String& value) {
    String hexstring = value;
    long number = strtol(&hexstring[0],NULL,16);
    
    // Split them up into r, g, b values
    long r = number >> 16;
    long g = number >> 8 & 0xFF;
    long b = number & 0xFF;

    color = jewel.Color(r,g,b);
    
    EffectChange = 1;
    jewelNode.setProperty("color").send(value);
}

bool brightnessHandler (const HomieRange& range, const String& value) {
  long brightness = value.toInt();
  Serial.println(brightness);
  setBrightness(brightness);
  jewelNode.setProperty("brightness").send(value);
}

void setBrightness(long brightness){
  if (brightness >= 0 && brightness <= MaxBrightness){
    jewel.setBrightness(brightness);
    jewel.show();
  }
}

void SelectEffect (String effect){
  if (effect == "fade"){ //fade red
    jewel.FadeInOut(color,10); 
      
  } else if (effect == "rainbow"){ //RainbowCycleAll
    jewel.rainbowCycleAll(50);
    
  } else if (effect == "heartbeat"){ //HeartBeat
    jewel.heartBeat(color);
  
  } else if (effect == "none"){
    jewel.NoEffect();
    jewel.fill(color);
    jewel.show();
    
  } else if (effect == "alarm"){
    jewel.alarm(jewel.Color(250,0,0));
    setBrightness(MaxBrightness);
    jewelNode.setProperty("brightness").send(String(MaxBrightness));
    //sent Brightness to NodeRed!!!
    
  } else if (effect == "call"){
    jewel.NoEffect();
    jewel.fill(jewel.Color(0,0,250));
    setBrightness(MaxBrightness);
    jewel.show();
    jewelNode.setProperty("brightness").send(String(MaxBrightness));
    //sent Brightness to NodeRed!!!

  } else if (effect == "donotdisturb"){
    jewel.NoEffect();
    jewel.fill(jewel.Color(125,0,125));
    setBrightness(MaxBrightness);
    jewel.show();
    jewelNode.setProperty("brightness").send(String(MaxBrightness));
    //sent Brightness to NodeRed!!!
    
  } else if (effect == "comeIn"){
    jewel.NoEffect();
    jewel.fill(jewel.Color(0,250,0));
    setBrightness(MaxBrightness);
    jewel.show();
    jewelNode.setProperty("brightness").send(String(MaxBrightness));
    //sent Brightness to NodeRed!!!
  }
}

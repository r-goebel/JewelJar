//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Effects.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2
int NUMPIXELS = 7;

Effects jewel = Effects(NUMPIXELS, PixelPin, NEO_GRB + NEO_KHZ800);

//Definition of possible effects
char* effectList[] = {"fade red", "fade cyan", "fade green", "rainbow cycle", "heart beat"};
int NumberEffects = 5;
int SelectedNew = random(0,NumberEffects);    //initial definition of new selected effect
int Selected;
bool EffectChange = 1;                        //variable indication change in effect (0=no change, 1=change), initially one change necessary 


//Definition of Switch
#define PinSwitch D6
int intervalSwitch = 500; //interval in which no new Switch is allowed
int lastSwitch;

void setup() {
  Serial.begin(115200);

  jewel.begin();
  jewel.setBrightness(150);

  jewel.show();
}

void loop() {

  //if switch state is HIGH, Change Effect
  if (millis()-lastSwitch > intervalSwitch){
    if (digitalRead(PinSwitch) == HIGH){
      EffectChange = 1;
      if (Selected < NumberEffects-1){
        SelectedNew = Selected+1;
      } else {
        SelectedNew = 0;
      }
      lastSwitch = millis();
    }
  }

  if (EffectChange == 1){
    Serial.println("EffectChange noticed");
    Selected = SelectedNew;
    EffectChange = 0;
    jewel.clear();
    //Initialization
    SelectEffect();
  }
  //no Change: just update effect
  else{
    jewel.Update();
  }
  
}


void SelectEffect (){
  if (Selected == 0){ //fade red
    jewel.FadeInOut(jewel.Color(255,0,0),10); 
    
  } else if (Selected == 1){ //fade cyan
    jewel.FadeInOut(jewel.Color(0,255,255),10); 
    
  } else if (Selected == 2){ //fade green
    jewel.FadeInOut(jewel.Color(0,255,0),10); 
    
  } else if (Selected == 3){ //RainbowCycleAll
    jewel.rainbowCycleAll(50);
    
  } else if (Selected == 4){ //HeartBeat
    jewel.heartBeat(jewel.Color(255,0,0));
  }     
}

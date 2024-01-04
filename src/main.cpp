#include <Arduino.h>
#include <FastLED.h>
#include "lSerial.h"
#include "loLED.h"
#define NUM_LEDS 3
#define DATA_PIN 6
CRGB led[NUM_LEDS];

lRGB leds[NUM_LEDS]; 
void setup()
{


    DDRD = DDRD | ( 1 << 1) ;
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(led, NUM_LEDS);  // GRB ordering is assumed
    lSInit(9600);
    //Serial.begin(9600);
    init(DATA_PIN, NUM_LEDS, leds);
    leds[0].r = 255;
    leds[0].g = 0;
    leds[0].b = 0;
    leds[1].r = 0;
    leds[1].g = 255;
    leds[1].b = 0;
    leds[2].r = 0;
    leds[2].g = 0;
    leds[2].b = 255;

    leds[0].r = 255;
    leds[0].g = 0;
    leds[0].b = 0;
    leds[1].r = 0;
    leds[1].g = 255;
    leds[1].b = 0;
    leds[2].r = 0;
    leds[2].g = 0;
    leds[2].b = 255;

    
    delay(1000);

    
}
float offset = .0;
void loop()
{
    delay(16);
    writeLEDs();
    writeChararray("hahaha dies ist ein test");    
    //Serial.println("test");
    //char r;
    //if(!readByte(r) == 1)
    //{
    //    writeChar(r);
    //}
   // writeChar(serialBuffer[0]);
   //if(Serial.available() > 0)
   //{
   //     Serial.println(Serial.read());
   //}
}

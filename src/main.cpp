#include <Arduino.h>
#include <FastLED.h>
#include "loLED.h"
#define NUM_LEDS 20
#define DATA_PIN 9

lRGB leds[NUM_LEDS]; 
void setup()
{
    Serial.begin(9600);
    loLED::init(6, 10, leds);
    for(int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].r = 177;
        leds[i].g = 100;
        leds[i].b = 59;
    }
    //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}

void loop()
{
    delay(16);
    loLED::writeLEDs();
    //leds[0] = CRGB::White; FastLED.show(); delay(3000);
	//leds[0] = CRGB::Black; FastLED.show(); delay(3000);
}

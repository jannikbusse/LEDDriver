#include <Arduino.h>
#include <FastLED.h>
#include "loLED.h"
#define NUM_LEDS 1
#define DATA_PIN 6
CRGB led[NUM_LEDS];

lRGB leds[NUM_LEDS]; 
void setup()
{
    Serial.begin(9600);

    for(int i = 0; i < NUM_LEDS; i++)
    {
        led[i] = CRGB(255,255,255);
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(led, NUM_LEDS);  // GRB ordering is assumed
    init(6, NUM_LEDS, leds);
    
    delay(2000);

    
}
float offset = .0;
void loop()
{
    delay(6);
    //writeLEDs();
    //leds[0] = CRGB::White; FastLED.show(); delay(3000);
	//leds[0] = CRGB::Black; FastLED.show(); delay(3000);
    offset += 0.1f;

    FastLED.show();
    

}

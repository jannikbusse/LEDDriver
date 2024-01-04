#include <Arduino.h>
#include <FastLED.h>
#include "loLED.h"
#define NUM_LEDS 3
#define DATA_PIN 6
CRGB led[NUM_LEDS];

lRGB leds[NUM_LEDS]; 
void setup()
{
    Serial.begin(9600);

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(led, NUM_LEDS);  // GRB ordering is assumed
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
    //leds[0] = CRGB::White; FastLED.show(); delay(3000);
	//leds[0] = CRGB::Black; FastLED.show(); delay(3000);
    //offset += 0.1f;
    //FastLED.show();
    Serial.println("hallo");
}

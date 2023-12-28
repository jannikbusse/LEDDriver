#include <Arduino.h>

//t0h 0.4 
//t1h 0.8
//t0l 0.85
//t1l0.45
//res above 50 
static int _PIN_NUM = 0;
static int _NUM_LEDS = 10;
    
struct lRGB
{
    uint8_t r = 100;
    uint8_t g = 100;
    uint8_t b = 100;

};

lRGB* _leds;

inline void write0H()
{
    asm volatile (
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    //"nop" "\n\t" // 1 cycle
  );
}

inline void write1H()
{
    asm volatile (
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
  );
}

inline void write0L()
{
    asm volatile (
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
  );
}

inline void write1L()
{
    asm volatile (
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
  );
}


inline void setBit()
{
    PORTD |= (1<<_PIN_NUM);
}

inline void dropBit()
{
    PORTD &= ~(1<<_PIN_NUM);
}

namespace loLED
{

   
    int init(int pinNumber, int ledCount, lRGB* leds)
    {
        if(pinNumber < 2 || pinNumber > 7)
            return -1;

        _PIN_NUM    =  pinNumber;
        _NUM_LEDS   =  ledCount;
        DDRD        = DDRD | ( 1 <<_PIN_NUM) ;
        _leds       = leds;    
        Serial.println("Init loLED");
        return 0;
    }



    int writeLEDs()
    {
        noInterrupts();
        dropBit();
        PORTD &= ~(1<<_PIN_NUM);
        delayMicroseconds(300);
        for(int l = 0; l < _NUM_LEDS+10; l++)
        {
            //
            /*for(bool* i = (bool*)_leds; i < (bool*)_leds + 24; i ++)
            {
                switch(*i)
                {
                case 1:
                    setBit();
                    write1H(); 
                    dropBit();
                    write1L();
                    setBit();
                break;
                
                case 0:
                    setBit();
                    write0H(); 
                    dropBit();
                    write0L();
                    setBit();
                break;
                }
                
            }
            */
            for(int i=0; i < 24; i ++)
            {
                    setBit();
                    asm volatile (
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    );
                    PORTD &= ~(1<<_PIN_NUM);
                    asm volatile (
                    //"nop" "\n\t" // 1 cycle
                    //"nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    "nop" "\n\t" // 1 cycle
                    //////////////"nop" "\n\t" // 1 cycle
                    );
            }
            setBit();
        }

        interrupts();
    }



}

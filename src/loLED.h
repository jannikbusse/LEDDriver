#include <Arduino.h>

//t0h 0.4 
//t1h 0.8
//t0l 0.85
//t1l0.45
//res above 50 
static uint8_t  _PIN_NUM = 0;
static int      _NUM_LEDS = 10;
    
struct lRGB
{
    uint8_t r = 100;
    uint8_t g = 100;
    uint8_t b = 100;

};

lRGB* _leds;



inline void writeOne()
{
    bitSet(PORTD,_PIN_NUM );
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

    bitClear(PORTD, _PIN_NUM);
    //PORTD &= ~(1<<_PIN_NUM);
    asm volatile (
    //"nop" "\n\t" // 1 cycle
    //"nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    "nop" "\n\t" // 1 cycle
    //////////////"nop" "\n\t" // 1 cycle
    );

}

inline void writeZero()
{
    asm volatile (
    "sbi %0, %[bit]\n\t"
    "nop        \n\t" // 1 cycle
    "nop        \n\t" // 1 cycle
    "nop        \n\t" // 1 cycle
    "nop        \n\t" // 1 cycle
    "nop        \n\t" // 1 cycle
    "cbi %0, %[bit]\n\t"
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
   // "nop        \n\t" // 1 cycle
    //////////////"nop" "\n\t" // 1 cycle
         : : "I" (_SFR_IO_ADDR(PORTD)), [bit]"I" (_PIN_NUM)
     );

}

template<uint8_t BIT> 
inline void writeNBitOne(uint8_t b)
{
    switch((b >> (7-BIT)) & ( 0b01))
    {
        case 1:
        writeOne();
    break;
        case 0:
        writeZero();
    break;
    }
}

inline void setBit()
{
    PORTD |= (1<<_PIN_NUM);
}

inline void dropBit()
{
    PORTD &= ~(1<<_PIN_NUM);
}



   
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



    volatile int writeLEDs()
    {
        noInterrupts();
        bitClear(PORTD, _PIN_NUM);
        delayMicroseconds(1000);
        for(int l = 0; l < _NUM_LEDS; l++)
        {
            
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);
        writeNBitOne<0>(0);

        interrupts();
    }
}




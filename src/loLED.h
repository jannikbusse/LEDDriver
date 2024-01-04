#include <Arduino.h>

#define WAIT_SHORT asm volatile (\
    "nop        \n\t"\
    );\

#define WAIT_LONG asm volatile (\
    "nop        \n\t"\
    "nop        \n\t"\
    "nop        \n\t"\ 
    "nop        \n\t"\
    "nop        \n\t"\
    "nop        \n\t"\
    "nop        \n\t"\
    );\


//t0h 0.4 
//t1h 0.8
//t0l 0.85
//t1l0.45
//res above 50 
static uint8_t  _PIN_NUM = 0;
static int      _NUM_LEDS = 10;

uint8_t high_mask   = 0;
uint8_t low_mask    = 0;


    
struct lRGB
{
    uint8_t r = 100;
    uint8_t g = 100;
    uint8_t b = 100;
    
    void set (uint8_t _r, uint8_t _g,uint8_t _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }




};

lRGB* _leds;



inline __attribute__((always_inline)) void writeOne()
{
    PORTD = high_mask ;
    WAIT_LONG
    PORTD = low_mask ;
    WAIT_SHORT

}

inline __attribute__((always_inline)) void writeZero()
{
    PORTD = high_mask ;
    WAIT_SHORT
    PORTD = low_mask ;
    WAIT_LONG
  
}
inline __attribute__((always_inline)) void writeOneEND()
{
    PORTD = high_mask ;
    WAIT_LONG
    PORTD = low_mask ;

}

inline __attribute__((always_inline)) void writeZeroEND()
{
    PORTD = high_mask ;
    WAIT_SHORT
    PORTD = low_mask ;
    WAIT_SHORT
  
}

template<uint8_t BIT> 
inline __attribute__((always_inline)) void writeNBit(const uint8_t b)
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

inline __attribute__((always_inline)) void writeNBitEND(const uint8_t b)
{
    switch((b & 0b01))
    {
        case 1:
        writeOneEND();
    break;
        case 0:
        writeZeroEND();
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
        return 0;
    }



    volatile int writeLEDs()
    {
        noInterrupts();
        bitClear(PORTD, _PIN_NUM);
        delayMicroseconds(1000);
        //uint8_t r = 0b11100010;
        uint8_t r = 0b00000000;
        uint8_t g = 0b00000000;
        uint8_t b = 0b00000000;

        high_mask = PORTD | ( 1 <<_PIN_NUM) ;
        low_mask = PORTD & ~( 1 <<_PIN_NUM) ;
        lRGB* led = &_leds[0];
        lRGB* endptr = &_leds[_NUM_LEDS];

        

        while(led != endptr)
        {
                
        writeNBit<0>(led->g);
        writeNBit<1>(led->g);
        writeNBit<2>(led->g);
        writeNBit<3>(led->g);
        writeNBit<4>(led->g);
        writeNBit<5>(led->g);
        writeNBit<6>(led->g);
        writeNBit<7>(led->g);

        writeNBit<0>(led->r);
        writeNBit<1>(led->r);
        writeNBit<2>(led->r);
        writeNBit<3>(led->r);
        writeNBit<4>(led->r);
        writeNBit<5>(led->r);
        writeNBit<6>(led->r);
        writeNBit<7>(led->r);
        
        writeNBit<0>(led->b);
        writeNBit<1>(led->b);
        writeNBit<2>(led->b);
        writeNBit<3>(led->b);
        writeNBit<4>(led->b);
        writeNBit<5>(led->b);
        writeNBit<6>(led->b);
        writeNBitEND(led->b);
        led ++;
    }
     interrupts();

     Serial.println(_leds[0].r);
}




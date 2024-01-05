
#include <Arduino.h>


unsigned int _baudrate = 9600;
unsigned long _wait_duration = 0; //this is in us

char serialBuffer[256];
uint8_t bufPos = 0;
uint8_t idx = 0;
uint8_t head = 0;
uint8_t available = 0;
bool lastBit = 1;
bool currentTransition = 0;

bool readLineState = 0;


template<uint8_t BIT>
inline __attribute__((always_inline)) void sWriteNBit(const uint8_t b)
{
    switch((b >> (7-BIT)) & ( 0b01))
    {
        case 1:
            PORTD = PORTD | 1 << 1;
    break;
        case 0:
            PORTD = PORTD & ~(1 << 1);
    break;
    }
}

inline __attribute__((always_inline)) void writeHigh()
{
    PORTD = PORTD | 1 << 1;
}
inline __attribute__((always_inline)) void writeLow()
{
    PORTD = PORTD & ~(1 << 1);
}


int lSInit(unsigned int baudrate)
{
    _baudrate = baudrate;
    _wait_duration = 1000000/baudrate -1;
    DDRD = DDRD | 1 << 1;
    DDRD = DDRD & 0b11111110;

    cli();
    //set timer2 interrupt at 8kHz
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    // set compare match register for 8khz increments
    OCR2A = 211;// = (16*10^6) / (8000*8) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);   
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    //hardware interupt
    PCICR |= 0b00000100;
    PCMSK2 |= 0b00000001;
    readLineState = PIND & 0b00000001;
    writeHigh();
    sei();
}

ISR (PCINT2_vect)
{
    if(!currentTransition && ((PIND & 0b00000001) == 0))
    {
        TCNT2  = 213;
        currentTransition = true;
    }
 
}

ISR(TIMER2_COMPA_vect){//timer1 interrupt 8kHz toggles pin 9
    uint8_t bit = PIND & 0b00000001;
  
    
    if(currentTransition && idx > 7)
    {
        idx = 0;
        currentTransition = 0;
        available ++;
        bufPos ++;
    }

    else if(currentTransition)
    {
        serialBuffer[bufPos] &= ~(1 << (idx)); 
        serialBuffer[bufPos] |= bit << (idx); 
        idx ++;

    }
}

int readByte(char &r)
{
    if(available == 0)
        return -1;
    r = serialBuffer[head];
    head ++;
    available --;
    return 1;
}



void writeChar(const char c)
{
    writeLow();
    delayMicroseconds(_wait_duration+3);
    sWriteNBit<7>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<6>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<5>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<4>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<3>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<2>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<1>(c);
    delayMicroseconds(_wait_duration);
    sWriteNBit<0>(c);
    delayMicroseconds(_wait_duration);
    writeHigh();
    delayMicroseconds(_wait_duration+3);
}

void writeChararray(const char *arr)
{
    while(*arr != '\0')
    {
        writeChar(*arr);
        arr ++;
    }
    writeChar('\r');
    writeChar('\n');

}
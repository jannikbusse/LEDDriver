
#include <Arduino.h>


unsigned int _baudrate = 9600;
unsigned long _wait_duration = 0; //this is in us


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

int lSInit(unsigned int baudrate)
{
    _baudrate = baudrate;
    _wait_duration = 1000000/baudrate -1;
    PORTD = PORTD | 1 << 1;
}


inline __attribute__((always_inline)) void writeHigh()
{
    PORTD = PORTD | 1 << 1;
}
inline __attribute__((always_inline)) void writeLow()
{
    PORTD = PORTD & ~(1 << 1);
}

void writeChar(char c)
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
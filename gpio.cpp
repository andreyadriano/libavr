#include "gpio.h"
#include <avr/io.h>

GPIO::GPIO(int pin, int mode)
{
    if (pin<8) // PORTD
    {
        port = PORT_D;
        mask = (1 << pin);
    }
    else // PORTB
    {
        port = PORT_B;
        mask = (1 << (pin-8));
    }

    if (port == PORT_B)
    {
        if (mode == OUTPUT)
        {
            // RMU - read, modify, update
            DDRB |= mask;
        }
        else if (mode==INPUT)
        {
            DDRB &= ~mask;
        }
    }
    else if (port == PORT_D)
    {
        if (mode == OUTPUT)
        {
            // RMU - read, modify, update
            DDRD |= mask;
        }
        else if (mode==INPUT)
        {
            DDRD &= ~mask;
        }
    }
}

GPIO::~GPIO()
{

}

bool GPIO::read()
{
    if(port == PORT_B)
    {
        return (PINB & mask) > 0;
    }
    else if (port == PORT_D)
    {
        return (PIND & mask) > 0;
    }
    return false;
}

void GPIO::write(bool valor)
{
    if(port == PORT_B)
    {
        if(valor){
            PORTB |= mask;
        }
        else
        {
            PORTB &= ~mask;
        }
    }
    else if (port == PORT_D)
    {
        if(valor){
            PORTD |= mask;
        }
        else
        {
            PORTD &= ~mask;
        }
    }
}
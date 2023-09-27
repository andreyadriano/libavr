#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

GPIO::IntHandler_t GPIO::int_handler[2] = {0,0};

GPIO::GPIO(int pin, int mode)

{
    initialize_port(pin,mode);
}
void GPIO::initialize_port(int pin,int mode)
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

GPIO::GPIO(int pin, int mode,IntHandler_t handler)

{
    initialize_port(pin,mode);
    int i =pin - 2;
    int int_mask= 0x3 <<2*i;

    int_handler[i] = handler;

    unsigned char sense = (mode-3) << 2 * i;
    EICRA = (EICRA & ~int_mask) | sense;

    EIMSK |= 0x01 << i;

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
            PORTD &= mask;
        }
    }
}

ISR(INT0_vect)
{
    GPIO::int_handler[0]();
}

ISR(INT1_vect)
{
    GPIO::int_handler[1]();
}
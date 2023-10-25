#include "timer.h"
#include <avr/io.h>
#include "avr/interrupt.h"

Timer * Timer::current_timer = 0;

Timer::Timer(Microseconds t1) : tick_length(t1), ticks(0)
{
    /**
     * Configurar Timer
     * normal mode
     * interrupcao do overflow
     * 1a versao (usar prescaler fixo)
     * 2a versao com base no tick_length
     * 
     * calcular melhor prescaler
     * ajustar inicio do TCNT0
    */

    current_timer = this;

    unsigned char prescaler = 3, pulse_count = 256;
    if(t1 == 1000)
    {
        TCCR0A = 0x00;
        TCCR0B = prescaler & 0x07;
        TIMSK0 = (1 << TOIE0);

        tcnt_base = 0xff - pulse_count + 1;
        TCNT0 = tcnt_base;
        current_timer = this;
    }

}

Timer::~Timer() {}

void Timer::isr_handler()
{
    ticks++;
}

Ticks Timer::get_ticks()
{
    return ticks;
}

Microseconds Timer::get_tick_length()
{
    return tick_length;
}

ISR(TIMER0_OVF_vect)
{
    Timer::current_timer->isr_handler();
}
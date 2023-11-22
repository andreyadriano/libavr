#include "timer.h"
#include <avr/io.h>
#include "avr/interrupt.h"

Timer * Timer::current_timer = 0;

Timer::Timer(Microseconds tl) : tick_length(tl), ticks(0)
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

    unsigned char prescaler = 3;
    int pulse_count = 256;
    if (tl == 100) {
        prescaler = 3; // div 64
        pulse_count = 25;
    }
    else if (tl == 500)
    {
        prescaler = 3; // div 64
        pulse_count = 125;
    }
    else if (tl == 1000)
    {
        prescaler = 3; // div 64
        pulse_count = 250;
    }
    else if (tl == 2000)
    {
        prescaler = 4; // div 256
        pulse_count = 125;
    }
    else if (tl == 4000)
    {
        prescaler = 4; // div 256
        pulse_count = 250;
    }
    else if (tl == 8000)
    {
        prescaler = 5; // div 1024
        pulse_count = 125;
    }
    else if (tl == 9984)
    {
        prescaler = 5; // div 1024
        pulse_count = 156;
    }
    else if (tl == 16000)
    {
        prescaler = 5; // div 1024
        pulse_count = 250;
    }
    else
    {
        prescaler = 5; // div 1024
        pulse_count = 250;
        tick_length = 16384;
    }

    TCCR0A = 0x00;
    TCCR0B = prescaler & 0x07;
    TIMSK0 = (1 << TOIE0);

    tcnt_base = 0xff - pulse_count + 1;
    TCNT0 = tcnt_base;
    current_timer = this;

}

Timer::~Timer() {}

void Timer::isr_handler()
{
    TCNT0 = tcnt_base;
    ticks++;

    for (int i=0; i<observers.size(); i++)
    {
        observers.get(i)->update(this->tick_length);
    }
}

Ticks Timer::get_ticks()
{
    return ticks;
}

Microseconds Timer::get_tick_length()
{
    return tick_length;
}

Ticks Timer::us_to_ticks(Microseconds us)
{
    return us/tick_length;
}

Ticks Timer::ms_to_ticks(Milliseconds ms)
{
    return ms/(tick_length/1000);
}

Ticks Timer::ticks_to_us(Ticks ticks)
{
    return ticks*tick_length;
}

Ticks Timer::ticks_to_ms(Ticks ticks)
{
    return ticks*(tick_length/1000);
}

void Timer::delay(Ticks ts)
{
    Ticks end = ticks + ts;
    while(ticks < end) ;
}

void Timer::register_observer (Observer<Microseconds> * obs)
{
    this->observers.insert(obs);
}

ISR(TIMER0_OVF_vect)
{
    Timer::current_timer->isr_handler();
}
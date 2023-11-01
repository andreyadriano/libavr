#ifndef __TIMER_H__
#define __TIMER_H__

typedef unsigned long long Ticks;
typedef Ticks Milliseconds;
typedef Ticks Microseconds;

class Timer {
private:
    Microseconds tick_length;
    Ticks ticks;
    unsigned char tcnt_base;
public:
    static Timer * current_timer;

    Timer(Microseconds t);
    ~Timer();

    void isr_handler();
    Ticks get_ticks();
    Microseconds get_tick_length();

    Ticks ms_to_ticks(Milliseconds ms);
    Ticks us_to_ticks(Microseconds us);
    Milliseconds ticks_to_ms(Ticks ticks);
    Microseconds ticks_to_us(Ticks ticks);

    void delay(Ticks tk); // busy wait
};

#endif

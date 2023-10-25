#ifndef __TIMER_H__
#define __TIMER_H__

typedef unsigned long long Ticks;
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
};

#endif

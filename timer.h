#ifndef __TIMER_H__
#define __TIMER_H__

class Timer {
private:
    int T;
public:
    Timer(int T);
    ~Timer();

    typedef unsigned long long ticks;
    typedef ticks Time;

    ticks get_ticks();

    Time get_tick_length();

    static void isr_handler();
};

#endif

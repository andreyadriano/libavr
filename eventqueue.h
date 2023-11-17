#ifndef __EVENT_QUEUE__
#define __EVENT_QUEUE__

#include "fifo.h"
#include <avr/interrupt.h>
#include "event.h"

template<int fsize>
class EventQueue
{
private:
    Fifo<Event*,fsize> events;
public:
    EventQueue(){};
    ~EventQueue(){};

    void pushEvent(Event* e)
    {
        cli();
        events.push(e);
        sei();
    }

    void run()
    {
        Event* e;
        while(events.size() > 0)
        {
            cli();
            e = events.pop();
            sei();
            e->func(e->args);
        }
    }

};

#endif

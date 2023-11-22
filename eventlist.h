#ifndef __EVENT_LIST__
#define __EVENT_LIST__

#include "list.h"
#include "event.h"
#include <avr/interrupt.h>

class EventList : private List<Event*>
{
private:

public:
    EventList();
    ~EventList();

    void pushEvent(Event* e)
    {
        // insere evento na lista
        cli();
        this->insert(e);
        sei();

    }

    void run()
    {
        // se há algo na lista remove e executa
        Event* e;
        while(this->size() > 0)
        {
            cli();
            e = this->remove_head();
            sei();
            e->func(e->args);
        }
    }
};

EventList::EventList(/* args */)
{
}

EventList::~EventList()
{
}

#endif

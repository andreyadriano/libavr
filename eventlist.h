#ifndef __EVENT_LIST__
#define __EVENT_LIST__

#include "list.h"
#include "event.h"
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include <stdio.h>

class EventList 
{
public:
    virtual ~EventList() {}

    virtual void pushEvent(Event* e) {}
    void run() {}
};

class EventListEDD : public EventList
{
private:
    List<Event*, true, Microseconds, true> list;
    Timer * timer;
    UART * uart;
public:
    EventListEDD(Timer * timer, UART * uart) : timer(timer), uart(uart) {}
    virtual ~EventListEDD() {}

    virtual void pushEvent(Event* e)
    {
        // insere evento na lista
        cli();
        list.insert_ordered(e,e->deadline);
        sei();
    }

    virtual void run()
    {
        // se há algo na lista remove e executa
        Event* e;
        while(list.size() > 0)
        {
            cli();
            e = list.remove_head();
            sei();
            e->func(e->args);
            // Microseconds now = timer->ticks_to_us(timer->get_ticks());

            // if (now >= e->deadline)
            // {
            //     // Aqui verifica se o tempo de execução é maior que o deadline e avisa sobre a falha
            //     uart->puts("Deadline missed!\n");
            // }
        }
    }


};

class PriorityList : public EventList
{
private:
    List<Event*, true> list;
public:
    virtual ~PriorityList() {}

    virtual void pushEvent(Event* e)
    {
        // insere evento na lista
        cli();
        list.insert(e, e->release_time);
        sei();
    }

    virtual void run()
    {
        // se há algo na lista remove e executa
        Event* e;
        while(list.size() > 0)
        {
            cli();
            e = list.remove_head();
            sei();
            e->func(e->args);
        }
    }
};

class EventFIFO : private List<Event*>
{
private:
    List<Event*> list;
public:
    virtual ~EventFIFO() {}

    virtual void pushEvent(Event* e)
    {
        // insere evento na lista
        cli();
        list.insert(e);
        sei();
    }

    virtual void run()
    {
        // se há algo na lista remove e executa
        Event* e;
        while(list.size() > 0)
        {
            cli();
            e = list.remove_head();
            sei();
            e->func(e->args);
        }
    }
};

#endif

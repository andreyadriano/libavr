#ifndef __EVENT_SCHEDULE_H__
#define __EVENT_SCHEDULE_H__

#include "list.h"
#include "event.h"
#include "timer.h"
#include "eventlist.h"
#include "observer.h"

class EventSchedule : public Observer<Microseconds>
{
private:
    List<Event*, true, Microseconds, true> events;
    EventList * elist;
public:
    EventSchedule(EventList * el) : elist(el) {}
    ~EventSchedule() {}

    void schedule_event(Event *e)
    {
        events.insert_ordered(e,e->release_time);
    }

    void update(Microseconds v)
    {
        Microseconds updated = events.update_head_rank(v);
        if (updated <= 0)
        {
            Event * e = events.remove_head();
            elist->pushEvent(e);
        }
    }
};


#endif
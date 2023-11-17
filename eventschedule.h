#ifndef __EVENT_SCHEDULE_H__
#define __EVENT_SCHEDULE_H__

#include "list.h"
#include "event.h"
#include "timer.h"
#include "eventlist.h"

class EventSchedule
{
private:
    List<Event*, true, Microseconds, true> events;
    EventList * elist;
public:
    EventSchedule(/* args */){}
    ~EventSchedule(){}

    void schedule_event(Event *e)
    {
        events.insert_ordered(e,e->release_time);
    }

    void update_list(Microseconds v)
    {
        Microseconds updatedTime = events.update_head_rank(v);
        if (updatedTime <= 0)
        {
            events.remove_head();
        }
    }
};


#endif
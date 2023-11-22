#ifndef __EVENT_H__
#define __EVENT_H__

#include "timer.h"

typedef void (*EventFuncPtr)(void*);

struct Event
{
    EventFuncPtr func;
    void * args;
    Microseconds release_time;
};

#endif
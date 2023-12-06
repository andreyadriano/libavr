#include "eventschedule.h"
#include "eventlist.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include <avr/interrupt.h>

PriorityList evlist;
EventSchedule evsched(&evlist);
Timer timer(8000);
UART uart;
char buffer[64];

Event str_1sec;
Event str_2sec;

void string_1sec(void * x)
{
    uart.puts("Evento 1 segundo\n");
    evsched.schedule_event(&str_1sec);
}

void string_2sec(void * x)
{
    uart.puts("Evento 2 segundos\n");
    evsched.schedule_event(&str_2sec);
}

void setup()
{
    uart.puts("Setup\n");
    
    timer.register_observer(&evsched);

    // Config Event 1 segundo
    str_1sec.func = string_1sec;
    str_1sec.release_time = 1000000;
    evsched.schedule_event(&str_1sec);

    // Config Event 2 segundos
    str_2sec.func = string_2sec;
    str_2sec.release_time = 2000000;
    evsched.schedule_event(&str_2sec);
}

void loop()
{
    evlist.run();
}

int main()
{
    setup();
    while(1) loop();
}
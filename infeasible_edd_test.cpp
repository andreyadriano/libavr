#include "eventschedule.h"
#include "eventlist.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include <avr/interrupt.h>

Timer timer(8000);
UART uart;
EventListEDD evlist(&timer, &uart);
EventScheduleEDD evsched(&evlist);
char buffer[64];

Event t0;
Event t1;
Event t2;
Event t3;
Event t4;

void task0(void * x)
{
    uart.puts("Task 0\n");
    timer.delay(timer.us_to_ticks(1000000));
}

void task1(void * x)
{
    uart.puts("Task 1\n");
    timer.delay(timer.us_to_ticks(2000000));
}

void task2(void * x)
{
    uart.puts("Task 2\n");
    timer.delay(timer.us_to_ticks(1000000));
}

void task3(void * x)
{
    uart.puts("Task 3\n");
    timer.delay(timer.us_to_ticks(4000000));
}

void task4(void * x)
{
    uart.puts("Task 4\n");
    timer.delay(timer.us_to_ticks(2000000));
}

void setup()
{
    uart.puts("Setup\n");
    
    timer.register_observer(&evsched);

    t0.func = task0;
    t0.release_time = 1000000;
    t0.deadline = 2000000;
    evsched.schedule_event(&t0);

    t1.func = task1;
    t1.release_time = 2000000;
    t1.deadline = 5000000;
    evsched.schedule_event(&t1);

    t2.func = task2;
    t2.release_time = 1000000;
    t2.deadline = 4000000;
    evsched.schedule_event(&t2);

    t3.func = task3;
    t3.release_time = 4000000;
    t3.deadline = 8000000;
    evsched.schedule_event(&t3);

    t4.func = task4;
    t4.release_time = 2000000;
    t4.deadline = 6000000;
    evsched.schedule_event(&t4);
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
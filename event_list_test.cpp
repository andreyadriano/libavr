#include "gpio.h"
#include "uart.h"
#include "adc_channel.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "timer.h"
#include "eventlist.h"
#include "event.h"

void int0_handler();
void button_pressed();

GPIO led(13, GPIO::OUTPUT);
GPIO button(2, GPIO::INTERRUPT_RISING,button_pressed);
UART uart;
ADC_Channel adc(0);
ADC_Channel adc1(1);
Timer timer(1000);
Ticks ticks_1s;
EventFIFO eventList;
Event buttonEvent;

volatile bool state;

void int0_handler()
{
    state =!state;
}

void button_pressed()
{
    state = 1;
    buttonEvent.args = (void*) 2;
    eventList.pushEvent(&buttonEvent);
}

void handleButtonEvent(void *arg)
{
    int button_num = (int) arg;

    char buff[16];
    sprintf(buff, "Botao %d\n", button_num);
    uart.puts(buff);
}

void setup()
{
    buttonEvent.func = handleButtonEvent;
    sei();
    uart.sync_puts("Setup");
    state = 0;

    // ticks_1s = timer.ms_to_ticks(1000);
}

void loop()
{
    // char buf[32];
    // led.write(state);
    // if (button.read()==1)
    //     uart.puts("Button\n");
    
    // while(uart.available() > 0)
    // {
    //     char c = uart.get() + 1;
    //     // sprintf(buf,"O valor incrementado é: %c\n", c);
    //     uart.puts(buf);
    // }
    
    // adc.start();
    // // sprintf(buf, "O ADC leu em A0: %d\n", adc.get());
    // uart.puts(buf);
    // adc.stop();

    // timer.delay(ticks_1s);
    // uart.sync_put('\n');

    eventList.run();

}

int main()
{
    setup();
    while(true) loop();
}


#include "gpio.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <stdio.h>

void int0_handler();

GPIO led(13, GPIO::OUTPUT);
GPIO button(3, GPIO::INTERRUPT_RISING,int0_handler);
UART uart;

bool state;

void int0_handler()
{
    state =!state;
}

void button_pressed()
{
    uart.sync_put('i');
    state = !state;
}

void setup()
{
    uart.sync_put('s');
    state = 0;
    sei();   
}

void loop()
{
    led.write(state);
    if (button.read()==1)
        uart.puts("Button\n");
    
    while(uart.available() > 0)
    {
        char c = uart.get() + 1;

        char buf[32];
        sprintf(buf,"O valor incrementado é: %c\n", c);
        uart.puts(buf);
    }
    
}

int main()
{
    setup();
    while(true) loop();
}


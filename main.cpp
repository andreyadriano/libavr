#include "gpio.h"
#include "uart.h"
#include "adc_channel.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "timer.h"

void int0_handler();

GPIO led(13, GPIO::OUTPUT);
GPIO button(3, GPIO::INTERRUPT_RISING,int0_handler);
UART uart;
ADC_Channel adc(0);
ADC_Channel adc1(1);
Timer timer(1000);

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
    char buf[32];
    led.write(state);
    if (button.read()==1)
        uart.puts("Button\n");
    
    while(uart.available() > 0)
    {
        char c = uart.get() + 1;

        // sprintf(buf,"O valor incrementado é: %c\n", c);
        uart.puts(buf);
    }
    
    adc.start();
    // sprintf(buf, "O ADC leu em A0: %d\n", adc.get());
    uart.puts(buf);
    adc.stop();

    int tks;

    if((tks = timer.get_ticks()) % 10 == 0)
    {
        sprintf(buf, "timer leu %u\n",tks);
        uart.puts(buf);
    }

}

int main()
{
    setup();
    while(true) loop();
}


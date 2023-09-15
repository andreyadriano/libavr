#include "gpio.h"
#include "uart.h"

GPIO led(13, GPIO::OUTPUT);
GPIO button(2, GPIO::INPUT);
UART uart;

void setup()
{
    uart.puts("Setup\n");
    uart.put(uart.get()+1);
}

void loop()
{
    led.write(button.read());

    if(button.read() == 1){
        uart.puts("Button\n");
    }
}

int main()
{
    setup();
    while(true) loop();
}

#include "gpio.h"

GPIO led(13, GPIO::OUTPUT);
GPIO button(2, GPIO::INPUT);

void setup()
{

}

void loop()
{
    led.write(button.read());
}

int main()
{
    setup();
    while(true) loop();
}

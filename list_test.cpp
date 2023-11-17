#include "uart.h"
#include <avr/interrupt.h>
#include <stdio.h>

#include "list.h"

UART uart;

void setup()
{
    sei();
    uart.puts("Setup\n");
}

List<int> list_int;

int main()
{
    setup();

    list_int.insert_tail(5);
    list_int.insert_tail(3);
    list_int.insert_tail(564);
    list_int.insert_tail(-654);
    list_int.insert_tail(900);
    
    char buf[16];

    // Lista
    for (int i = 0; i < list_int.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, list_int.get(i));
        uart.puts(buf);
    }

    // Remove cauda
    int rem = list_int.remove_tail();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < list_int.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, list_int.get(i));
        uart.puts(buf);
    }

    // Remove cabeça
    rem = list_int.remove_head();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < list_int.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, list_int.get(i));
        uart.puts(buf);
    }

    // Remove segunda cauda
    rem = list_int.remove_tail();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < list_int.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, list_int.get(i));
        uart.puts(buf);
    }

    // Remove cabeça
    rem = list_int.remove_head();
    sprintf(buf, "Removido: %d\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < list_int.size(); i++)
    {
        sprintf(buf, "Item %d: %d\n", i, list_int.get(i));
        uart.puts(buf);
    }

    while(1) ;

}

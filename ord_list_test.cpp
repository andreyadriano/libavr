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

List<char, true, int, true> ordList;

int main()
{
    setup();

    ordList.insert('c',5);
    ordList.insert('b',3);
    ordList.insert('d',564);
    ordList.insert('a',654);
    
    char buf[16];

    // Lista
    for (int i = 0; i < ordList.size(); i++)
    {
        sprintf(buf, "Item %d: %c, rank: %d\n", i, ordList.get(i), ordList.get_rank(i));
        uart.puts(buf);
    }
    
    int new_rank = ordList.update_head_rank(1);

    // Remove cauda
    char rem = ordList.remove_tail();
    sprintf(buf, "Removido: %c\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < ordList.size(); i++)
    {
        sprintf(buf, "Item %d: %c, rank: %d\n", i, ordList.get(i), ordList.get_rank(i));
        uart.puts(buf);
    }

    // Remove cabeça
    rem = ordList.remove_head();
    sprintf(buf, "Removido: %c\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < ordList.size(); i++)
    {
        sprintf(buf, "Item %d: %c, rank: %d\n", i, ordList.get(i), ordList.get_rank(i));
        uart.puts(buf);
    }

    // Remove segunda cauda
    rem = ordList.remove_tail();
    sprintf(buf, "Removido: %c\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < ordList.size(); i++)
    {
        sprintf(buf, "Item %d: %c, rank: %d\n", i, ordList.get(i), ordList.get_rank(i));
        uart.puts(buf);
    }

    // Remove cabeça
    rem = ordList.remove_head();
    sprintf(buf, "Removido: %c\n", rem);
    uart.puts(buf);

    // Lista
    for (int i = 0; i < ordList.size(); i++)
    {
        sprintf(buf, "Item %d: %c, rank: %d\n", i, ordList.get(i), ordList.get_rank(i));
        uart.puts(buf);
    }

    while(1) ;

}

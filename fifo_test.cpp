#include "fifo.h"
#include "uart.h"


int  main()
{
    UART uart;
    Fifo<char,26> fifo;
    for (char c='a';c<='z';c++){
        fifo.push(c);
    }
    uart.sync_put(fifo.pop());
    uart.sync_put(fifo.pop());
    uart.sync_put(fifo.pop());

    while(fifo.size()){
    uart.sync_put(fifo.pop());

}
    

    uart.sync_puts("\n\nterminou\n");
    while(true);


}

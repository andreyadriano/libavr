#ifndef __UART_H__
#define __UART_H__

#include "fifo.h"

class UART
{
public:
    UART();
    ~UART();

    void sync_put (unsigned char data);
    void sync_puts (const char * str);
    unsigned char sync_get();

    int available();

    void put (unsigned char data);
    void puts (const char * str);
    unsigned char get();

    static void rxc_handler();
    static void udre_handler();

private:
    static Fifo<unsigned char, 32> TxFifo;
    static Fifo<unsigned char, 32> RxFifo;
};


#endif
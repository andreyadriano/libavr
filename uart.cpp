#include "uart.h"
#include <avr/io.h>

UART::UART()
{
    unsigned int ubrr = 103;
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1 stop bit */
    UCSR0C = (3<<UCSZ00);
}

UART::~UART()
{
}

void UART::put(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0))) ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void UART::puts(const char * str)
{
    int i = 0;
    while(str[i] != '\0'){
        put(str[i]);
        i += 1;
    }
}

unsigned char UART::get()
{

}
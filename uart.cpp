#include "uart.h"
#include "avr/io.h"
#include "avr/interrupt.h"

Fifo<unsigned char, 32> UART::TxFifo;
Fifo<unsigned char, 32> UART::RxFifo;

UART::UART()
{
    unsigned int ubrr = 103;
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
   // Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (3<<UCSZ00);
}


UART::~UART()
{

}

void UART::sync_put(unsigned char data )
{
        /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)))
    ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void UART::sync_puts(const char * str)
{
    for (int i=0; str[i]!='\0';i++){
        sync_put(str[i]);
    }
}

unsigned char UART::sync_get()
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))
    ;
    /* Get and return received data from buffer */
    return UDR0;
}

int UART::available()
{
    return RxFifo.size();
}

void UART::put(unsigned char data )
{
    while (TxFifo.size() >= TxFifo.capacity()) ;

    cli();
    TxFifo.push(data);
    sei();
    UCSR0B |= (1 << UDRIE0);
}

void UART::puts(const char * str)
{
    for (int i=0; str[i]!='\0';i++){
        this->put(str[i]);
    }
}

unsigned char UART::get()
{
    while(RxFifo.size() == 0) ;
    cli();
    unsigned char data = RxFifo.pop();
    sei();
    return data;
}

ISR(USART_RX_vect) {UART::rxc_handler();}

void UART::rxc_handler()
{
    RxFifo.push(UDR0);
}

ISR(USART_UDRE_vect) {UART::udre_handler();}

void UART::udre_handler()
{
    if(TxFifo.size() == 0)
    {
        UCSR0B &= ~(1 << UDRIE0);
    }
    else
    {
        UDR0 = TxFifo.pop();
    }
}
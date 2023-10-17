#include "adc_channel.h"
#include <avr/io.h>
#include "avr/interrupt.h"
#include "uart.h"

UART teste;

ADC_Channel *ADC_Channel::active_channel;

ADC_Channel::ADC_Channel(int ch) : channel(ch)
{
    ADMUX = (ADMUX&0xF0) | (ch&0x0F) | (0 << REFS1) | (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

ADC_Channel::~ADC_Channel()
{
}

int ADC_Channel::sample()
{
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    return ADC;
}

void ADC_Channel::start()
{
    active_channel = this;
    ADCSRA |= (0 << ADEN);
    ADMUX = (ADMUX&0xF0) | (channel&0x0F);
    ADCSRA |= (1 << ADIE) | (1 << ADEN) | (1 << ADSC); // se setar o ADATE ele trava, testamos com ADIE e pelo menos não travou
}

void ADC_Channel::stop()
{
    ADCSRA &= ~(1 << ADEN);
}

int ADC_Channel::get()
{
    teste.sync_put('t');
    while (adc_fifo.size() == 0)
        ;

    cli();
    int data = adc_fifo.pop();
    sei();

    return data;
}

ISR(ADC_vect)
{
    ADC_Channel::adc_isr_handler();
}

void ADC_Channel::adc_isr_handler()
{
    cli();
    active_channel->adc_fifo.push(ADC);
    sei();
    // teste
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // seta o prescaler para 128 de novo (desativou ao ocorrer interrupção)
}
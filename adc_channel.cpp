#include "adc_channel.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ADC_Channel::ADC_Channel(int ch)
{
    channel = ch;

    // configurar ADC para single conversion
    ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
    // configurar canal e referencia
    ADMUX = (ADMUX&0xF0) | (ch&0x0F) | (0 << REFS1) | (1 << REFS0);
}

ADC_Channel::~ADC_Channel()
{

}

int ADC_Channel::sample()
{
    // inicia uma conversao
    ADCSRA |= (1 << ADSC);
    // aguarda conclusao de conversao
    while(ADCSRA & (0 << ADIF)){} ;
    // aguarda resultado de conversao
    return ADC;
}

void ADC_Channel::start(){
    ADCSRA |= (0 << ADEN);
    ADMUX = (ADMUX&0xF0) | (channel&0x0F);
    ADCSRA |= (1 << ADATE) | (1 << ADEN) | (1 << ADSC);
}

int ADC_Channel::get(){
    if(this->ADCFifo.size()>0){
        cli();
        int data = this->ADCFifo.pop();
        sei();
        return data;
    }
}

void ADC_Channel::adc_isr_handler()
{
    // cli();
    // this->ADCFifo.push(ADC);
    // sei();
}
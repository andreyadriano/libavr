#include "adc_channel.h"
#include <avr/io.h>

ADC_Channel::ADC_Channel(int ch)
{
    channel = ch;

    // configurar ADC para single conversion
    ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);

    ADMUX |= (0 << REFS1)|(1 << REFS0); // determina referencia
    
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
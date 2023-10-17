#ifndef _ADC_H_
#define _ADC_H_

#include "fifo.h"

class ADC_Channel
{
private:
    int channel;
    Fifo<int, 32> adc_fifo;
    static ADC_Channel *active_channel;

public:
    ADC_Channel(int ch);
    ~ADC_Channel();

    int sample();

    void start();

    void stop();

    int get();

    static void adc_isr_handler();
};

#endif
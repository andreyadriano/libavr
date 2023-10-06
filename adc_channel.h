#ifndef __ADC_H__
#define __ADC_H__

#include "fifo.h"

class ADC_Channel
{
public:
    ADC_Channel(int ch);
    ~ADC_Channel();

    int get();
    int sample();
    void start();
    void stop();
    static void adc_isr_handler();

private:
    int channel;
    Fifo<int,32> ADCFifo;
    static ADC_Channel * activeChannel;
};

#endif
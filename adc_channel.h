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

private:
    int channel;
    static void isr_handler();
};

#endif
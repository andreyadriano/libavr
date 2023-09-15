#ifndef __UART_H__
#define __UART_H__

class UART
{
public:
    UART(/* args */);
    ~UART();

    void put(unsigned char data);
    void puts(const char *str);
    unsigned char get();
};

#endif
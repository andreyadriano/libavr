#ifndef __GPIO_H__
#define __GPIO_H__

class GPIO
{
private:
    enum
    {
        PORT_B = 0,
        PORT_C = 1,
        PORT_D = 2
    };
    int port;
    unsigned char mask;
public:
    enum{
        INPUT = 0,
        OUTPUT = 1,
        INPUT_PULLUP = 2,
        INTERRUPT = 3
        };

    GPIO(int pin, int mode);
    ~GPIO();

    bool read();
    void write(bool valor);
};

#endif
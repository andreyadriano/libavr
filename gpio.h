
#ifndef  __GPIO_H__
#define  __GPIO_H__


#endif

class GPIO
{
private:
    enum
    {
        PORT_B=0,
        PORT_C=1,
        PORT_D=2
    };
    int port;
    unsigned char mask;

    void initialize_port(int pin,int mode);
    
public:
    enum
    {
        OUTPUT = 1,
        INPUT = 0,
        INPUT_PULLUP=2,
        INTERRUPT_LOW=3,
        INTERRUPT_CHANGE=4,
        INTERRUPT_FALLING = 5,
        INTERRUPT_RISING=6


    };

    typedef void (*IntHandler_t)(void);
    static IntHandler_t int_handler[2];

    GPIO(int pin, int mode);
    GPIO(int pin, int mode, IntHandler_t handler);

    ~GPIO();

    bool read();
    void write (bool val);
};



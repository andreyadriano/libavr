#ifndef __FIFO_H__
#define __FIFO_H__

template<typename T, int N>
class Fifo
{
private:
    char data [N];
    int s,h,t;

public:
Fifo(): s(0) , h(0), t(0){}
~Fifo(){}

void push(T d)
{
    data[t]=d;
    t = (t+1) % N;
    s++;

}

T pop()
{
    T ret = data[h];
    h = (h+1) % N;
    s--;
    return ret;    
}

int size()
{
    return s;
}

const int capacity()
{
    return N;
}

};

#endif




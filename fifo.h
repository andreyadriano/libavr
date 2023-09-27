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
    while(s == N);    
    data[t]=d;
    t = (t+1) % N;
    s++;

}

T pop()
{
    while(s == 0);
    T ret = data[h];
    h = (h+1) % N;
    s--;
    return ret;    
}

int size()
{
    return s;
}

};



#endif




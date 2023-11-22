#ifndef __OBSERVER_H__
#define __OBSERVER_H__

template<typename UPDATE_TYPE>
class Observer
{
    public:
        virtual ~Observer() {}
        virtual void update(UPDATE_TYPE v) {}
};

#endif
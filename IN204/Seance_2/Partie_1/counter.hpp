#ifndef CounterHPP
#define CounterHPP
#include <iostream>
 
class MyCounter
{
    public:
        MyCounter(): counter(0), max(0)
        {}

        MyCounter(unsigned max_counter): counter(0), max(max_counter)
        {}

        MyCounter(unsigned current_counter, unsigned max_counter): counter(current_counter), max(max_counter)
        {}

        MyCounter(const MyCounter& c): counter(c.counter), max(c.max)
        {}

        ~MyCounter()
        {
            std::cout << "Destructing counter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }
    
    unsigned counter;
    unsigned max;
 
    unsigned getCounter() const; // const sur la fonction indique juste que la fonction est read-only
    unsigned getMax() const;
    void increment();
 
    void reset();
    void set(unsigned value);
    void setMax(unsigned value);
};
 
class MyBiDiCounter: public MyCounter
{
    public:
        void decrement();
        void print();
};

#endif
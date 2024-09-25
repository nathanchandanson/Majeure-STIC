#ifndef CounterHPP
#define CounterHPP
#include <iostream>
 
class BaseCounter
{
    public: 
        unsigned counter;
        unsigned max;
 
        unsigned getCounter() const; // const sur la fonction indique juste que la fonction est read-only
        unsigned getMax() const;
        void print();
 
        void reset();
        void set(unsigned value);
        void setMax(unsigned value);
    
    protected: 
        // On définit les Constructeurs/Destructeurs comme protected, comme ça on ne peut pas créér d'objet BaseCounter
        BaseCounter(): counter(0), max(0)
        {}

        BaseCounter(unsigned max_counter): counter(0), max(max_counter)
        {}

        BaseCounter(unsigned current_counter, unsigned max_counter): counter(current_counter), max(max_counter)
        {}

        BaseCounter(const BaseCounter& c): counter(c.counter), max(c.max)
        {}

        ~BaseCounter()
        {
            std::cout << "Destructing counter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }

        // On définit ces méthodes comme protégée comme ça on ne peut pas y accéder depuis BaseCounter mais depuis les sous-classes
        void increment();
        void decrement();

};
 
class BackwardCounter: public BaseCounter
{
    public:
        BackwardCounter(): BaseCounter()
        {}

        BackwardCounter(unsigned max_counter): BaseCounter(max_counter)
        {}

        BackwardCounter(unsigned current_counter, unsigned max_counter): BaseCounter(current_counter, max_counter)
        {}
        
        BackwardCounter(const BackwardCounter& c): BaseCounter(c)
        {}

        ~BackwardCounter()
        {
            std::cout << "Destructing BackwardCounter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }

        using BaseCounter::decrement;
};

class ForwardCounter: public BaseCounter
{
    public:
        ForwardCounter(): BaseCounter()
        {}

        ForwardCounter(unsigned max_counter): BaseCounter(max_counter)
        {}

        ForwardCounter(unsigned current_counter, unsigned max_counter): BaseCounter(current_counter, max_counter)
        {}
        
        ForwardCounter(const ForwardCounter& c): BaseCounter(c)
        {}

        ~ForwardCounter()
        {
            std::cout << "Destructing ForwardCounter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }

        using BaseCounter::increment;
};

class BiDiCounter: public BaseCounter
{
    public:
        BiDiCounter(): BaseCounter()
        {}

        BiDiCounter(unsigned max_counter): BaseCounter(max_counter)
        {}

        BiDiCounter(unsigned current_counter, unsigned max_counter): BaseCounter(current_counter, max_counter)
        {}
        
        BiDiCounter(const BiDiCounter& c): BaseCounter(c)
        {}

        ~BiDiCounter()
        {
            std::cout << "Destructing BiDiCounter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }

        using BaseCounter::increment;
        using BaseCounter::decrement;
        void increment(unsigned value);
};

class AdvCounter: public BaseCounter
{
    public:
        AdvCounter(): BaseCounter()
        {}

        AdvCounter(unsigned max_counter): BaseCounter(max_counter)
        {}

        AdvCounter(unsigned current_counter, unsigned max_counter): BaseCounter(current_counter, max_counter)
        {}
        
        AdvCounter(const AdvCounter& c): BaseCounter(c)
        {}

        ~AdvCounter()
        {
            std::cout << "Destructing AdvCounter " << this << " : (" << this->counter << "," << this->max << ")" << std::endl;
        }

        void increment();
};

#endif
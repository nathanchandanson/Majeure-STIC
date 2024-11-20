#ifndef COUNTER_HPP
#define COUNTER_HPP
#include<iostream>

class BaseCounter
{
protected:
    unsigned counter;
    unsigned max;
 
public:
    unsigned getCounter() const { return counter; }
    unsigned getMax() const { return max; }
    void reset() { counter = 0; }
    void set(unsigned value) { counter = value; }
    void setMax(unsigned value)
    {
        max = value;
        if(value > counter)
            counter = counter % max;
    }
    friend std::ostream& operator <<(std::ostream& theStream, const BaseCounter& aCounter);
    virtual void next() = 0;            // Le =0 permet de dire au compilateur qu'on ne fournit pas d'implémentation de cette fonction
    virtual void next(unsigned theValue) = 0;
    virtual const char* getClassName() const = 0;
 
protected:
    BaseCounter(): counter(0), max(0) {}
    BaseCounter(unsigned theCounter,
        unsigned theMax): counter(theCounter), max(theMax)
    {}
    explicit BaseCounter(unsigned theMax):
        max(theMax), counter(0)
    {}
    BaseCounter(const BaseCounter& anotherCounter):
        counter(anotherCounter.counter),
        max(anotherCounter.max)
    {}
    ~BaseCounter()
    {}
};
 
class ForwardCounter: public virtual BaseCounter
{
public:
    void increment()
    {
        if(counter < max)
            counter = counter + 1;
        else
            counter = 0;
    }
    virtual void next() override {increment();}
    virtual void next(unsigned theValue) override
    {
        for(int i = 0; i < theValue; i++){
            increment();
        }
    }
    virtual const char* getClassName() const override {return "ForwardCounter";}

    ForwardCounter(): BaseCounter() {}
    ForwardCounter(const ForwardCounter& aCounter): BaseCounter(aCounter) {}
    explicit ForwardCounter(unsigned theMaxValue): ForwardCounter(0, theMaxValue) {}
    ForwardCounter(unsigned theCounter, unsigned theMaxValue): BaseCounter(theCounter, theMaxValue) {}
};
 
class BackwardCounter: public virtual BaseCounter
{
public:
    void decrement()
    {
        if(counter > 0)
            counter = counter -1;
        else
            counter = max;
    }
    virtual void next() override {decrement();}
    virtual void next(unsigned theValue) override
    {
        for(int i = 0; i < theValue; i++){
            decrement();
        }
    }
    virtual const char* getClassName() const override {return "BackwardCounter";}

    BackwardCounter(): BaseCounter() {}
    BackwardCounter(const ForwardCounter& aCounter): BaseCounter(aCounter) {}
    explicit BackwardCounter(unsigned theMaxValue): BackwardCounter(0, theMaxValue) {}
    BackwardCounter(unsigned theCounter, unsigned theMaxValue): BaseCounter(theCounter, theMaxValue) {}
};
 
class BiDiCounter: public ForwardCounter, public BackwardCounter
{
public:
    virtual void next() override
    {
        ForwardCounter::next();
    }
    virtual void next(unsigned aNumberOfSteps) override
    {
        ForwardCounter::next(aNumberOfSteps);
    }
    virtual const char* getClassName() const override {return "BiDiCounter";}

    BiDiCounter(): ForwardCounter(), BackwardCounter() {}
    BiDiCounter(const BiDiCounter& aCounter):
        ForwardCounter(aCounter),
        BackwardCounter((const BackwardCounter&)aCounter),
        BaseCounter(aCounter) {}
    BiDiCounter(unsigned theMaxValue): BiDiCounter(0, theMaxValue) {}
    BiDiCounter(unsigned theCounter, unsigned theMaxValue):
        ForwardCounter(theCounter, theMaxValue),
        BackwardCounter(theCounter, theMaxValue),
        BaseCounter(theCounter, theMaxValue) {}
};

void testNext(BaseCounter& aCounter);

#endif // COUNTER_HPP
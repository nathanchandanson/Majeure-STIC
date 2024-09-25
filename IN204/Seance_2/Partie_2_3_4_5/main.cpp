#include <iostream>
#include "counter.hpp"

void testFamilyOfCounters()
{
    ForwardCounter incCounter(0, 4);
    BackwardCounter decCounter(0, 3);
    BiDiCounter biDiCounter(0, 5);
    for(int i=0; i < 6; i++)
    {
        incCounter.increment();
        incCounter.print();
	    decCounter.decrement();
        decCounter.print();
        biDiCounter.increment();
        biDiCounter.print();
    }
    for(int i=0; i < 6; i++)
    {
        biDiCounter.decrement();
        biDiCounter.print();
    }
}

void testOldIncMethod() {
    BiDiCounter bidiCounter1(0, 5);
    for(unsigned i = 0; i <= 5; i++) 
    {
        bidiCounter1.increment();
        bidiCounter1.print();
    }
}

void testNewIncMethod() {
    BiDiCounter bidiCounter1(0, 5);
    for(unsigned i = 0; i <= 5; i++) 
    {
	bidiCounter1.increment(5);
        bidiCounter1.print();
    }
}

void testMyAdvCounter()
{
    AdvCounter incCounter(0, 4);
    for(int i=0; i < 6; i++)
    {
	  incCounter.increment();
        incCounter.print();
    }
}

// Marche pas parce que j'ai mis BaseCounter::increment en protected
// void testCounter(BaseCounter& unCompteur)
// {
//     for(int i=0; i < 6; i++)
//     {
//         unCompteur.increment();
//         unCompteur.print();
//     }
// }

int main()
{
    testFamilyOfCounters();
    // testNewIncMethod();
    // testOldIncMethod();
    // testMyAdvCounter();
    return 0;
}
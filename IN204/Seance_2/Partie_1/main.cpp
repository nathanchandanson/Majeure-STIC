#include <iostream>
#include "counter.hpp"

void testMyBiDiCounter()
{
    MyBiDiCounter counterA;
    counterA.setMax(4);
    counterA.reset();
    counterA.print();
    for (int i = 0; i < 6; i++)
    {
        counterA.increment();
        counterA.print();
    }
    for (int i = 0; i < 6; i++)
    {
        counterA.decrement();
        counterA.print();
    }
}

int main()
{
    testMyBiDiCounter();
    return 0;
}
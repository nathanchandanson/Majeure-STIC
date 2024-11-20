#include <iostream>
#include "counter.hpp"

// Faire Qu >=5

int main()
{
    ForwardCounter forward(10);
    BackwardCounter backward(7);
    std::cout << forward << std::endl;
    forward.next();
    std::cout << forward << std::endl;

    testNext(forward);
    testNext(backward);

    return 0;
}
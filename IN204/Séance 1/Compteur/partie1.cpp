#include <iostream>
#include "counter.hpp"

void useObjectA() {
    MyCounter Counter1;
    MyCounter Counter2;

    Counter1.setMax(2);
    Counter2.setMax(4);
    
    Counter1.reset();
    Counter2.reset();
    
    for(unsigned i = 0; i <= 5; i++) {
        std::cout 
	            << "Valeur des compteurs (" 	<< Counter1.counter 
	            << ", " << Counter2.counter 	<< ")" << std::endl;

        Counter1.increment();
        Counter2.increment();
    }
}

int main()
{
    useObjectA();
    return 0;
}
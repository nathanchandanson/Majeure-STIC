#include <iostream>
#include "complex.hpp"

Complex Complex::I = Complex::createFromCartesian(0.0,1.0);
Complex I = Complex::I;

int main()
{
    Complex test = 1 + I;
    test.print();
    test += I;
    test.print();

    std::cout << test;
    
    return 0;
}

// Question 5 : Ca marche pas parce qu'on a pas redéfini les opérateurs
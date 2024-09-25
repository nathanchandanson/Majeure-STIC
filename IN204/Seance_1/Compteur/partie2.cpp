#include <iostream>
#include "counter.hpp"

void useObjectA() {
    MyCounter Counter1 = MyCounter(2);
    MyCounter Counter2 = MyCounter(4);
    
    for(unsigned i = 0; i <= 5; i++) {
        std::cout 
	            << "Valeur des compteurs (" 	<< Counter1.counter 
	            << ", " << Counter2.counter 	<< ")" << std::endl;

        Counter1.increment();
        Counter2.increment();
    }
}

void myfunctionA()
{
  MyCounter counter;
  std::cout << counter.getCounter() << std::endl;
  std::cout << counter.getMax() << std::endl;
}
 
void myfunctionB() 
{
  MyCounter* counter = new MyCounter();
  std::cout << counter->getCounter() << std::endl;
  std::cout << counter->getMax() << std::endl;
  delete counter;
}

void test_copie()
{
  MyCounter compteur = MyCounter(12, 52);
  std::cout << "Compteur de départ : (" << compteur.counter << "," << compteur.max << ")" << std::endl;
  MyCounter compteur2 = MyCounter(compteur);
  std::cout << "Compteur de départ : (" << compteur.counter << "," << compteur.max << ")" << std::endl;
  std::cout << "Compteur d'arrivée : (" << compteur2.counter << "," << compteur2.max << ")" << std::endl;
}

int main()
{
    // myfunctionA();
    // myfunctionB();
    // useObjectA();
    test_copie();
    return 0;
}
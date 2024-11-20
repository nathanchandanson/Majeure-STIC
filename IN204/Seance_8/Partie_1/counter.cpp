#include "counter.hpp"

std::ostream& operator <<(std::ostream& theStream, const BaseCounter& aCounter)
{
    theStream << aCounter.getClassName() << " : "  << aCounter.getCounter() << "/" << aCounter.getMax();
    return theStream;
}

void testNext(BaseCounter& aCounter)
{
    for(int i = 0; i < 10; i++)
    {
        aCounter.next();
        std::cout << aCounter << std::endl;
    }
}
#include"interval.hpp"
#include<algorithm>
#include<iostream>
#include<vector>
 
template<class inputIterator>
void print(inputIterator beginIt, inputIterator endIt)
{
    if(beginIt == endIt)
    {
        std::cout << "[]" << std::endl;
        return;
    }    
    for(;;)
    {
        std::cout << *beginIt;
        beginIt++;
        if(beginIt == endIt)
            break;
        std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return;
}
 
void testInterval()
{
    interval inter(5, 15);
    std::cout << "Contenu de l'interval : "; 
    print(inter.begin(), inter.end());
    // Recherche du plus grand élément.
    auto maxIt = max_element(inter.begin(), inter.end());
    std::cout << "Element maximal de la séquence: " << *maxIt << std::endl;
    // Duplication des valeurs dans un vecteur
    std::vector<int> vec(inter.begin(), inter.end());
    std::cout << "Contenu du vecteur : "; 
    print(vec.begin(), vec.end());
}
 
int main()
{
    testInterval();
    return 0;
}
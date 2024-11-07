#include <iostream>
#include <list>
#include "simple_sort.hpp"

struct Toto
{
};

int main()
{
    std::list<int> l = {1, 7, 3, 4, 9, 2, 5};
    std::vector<int> v(l.begin(), l.end());
    simple_sort(l.begin(), l.end());
    std::cout << l << std::endl;
    simple_sort(v.begin(), v.end());
    std::cout << v << std::endl;
}
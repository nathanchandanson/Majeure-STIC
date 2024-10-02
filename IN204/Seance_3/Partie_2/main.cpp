#include <iostream>
#include "simple_sort.hpp"

int main()
{
    std::vector<int> array;
    generic::populate_with_randoms(array, 10, 1, 10);
    generic::print_vector(array);
    std::cout << "\n";
    generic::simple_sort(array);
    generic::print_vector(array);
    std::cout << "\n";
    generic::simple_sort<int, generic::lower_traits<int>>(array);
    generic::print_vector(array);
    return 0;
}
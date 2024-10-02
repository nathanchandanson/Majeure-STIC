#include "simple_sort.hpp"

int main()
{
    std::cout << "Premier vecteur" << std::endl;
    std::vector<int> vecteur1;
    monomorphic::populate_with_randoms(vecteur1, 10, 20, 40);
    monomorphic::print_vector(vecteur1);
    monomorphic::simple_sort(vecteur1);
    monomorphic::print_vector(vecteur1);

    std::cout << std::endl << "Deuxième vecteur" << std::endl;
    std::vector<int> vecteur2;
    generic::populate_with_randoms(vecteur2, 10, 20, 40);
    generic::print_vector(vecteur2);
    generic::simple_sort(vecteur2);
    generic::print_vector(vecteur2);

    std::cout << std::endl << "Troisième vecteur" << std::endl;
    std::vector<float> vecteur3;
    generic::populate_with_randoms(vecteur3, 10, 20.0, 40.0);
    generic::print_vector(vecteur3);
    generic::simple_sort(vecteur3);
    generic::print_vector(vecteur3);

    std::cout << std::endl << "Quatrième vecteur" << std::endl;
    std::vector<char> vecteur4;
    generic::populate_with_randoms(vecteur4, 10, 'A', 'Z');
    generic::print_vector(vecteur4);
    generic::simple_sort(vecteur4);
    generic::print_vector(vecteur4);

    return 0;
}
#ifndef simple_sortHPP
#define simple_sortHPP
 
#include<vector>
#include<random>
#include<iostream>
 
namespace monomorphic
{
    void populate_with_randoms(
        std::vector<int>& theVector,
      	int theNumberOfValues, int theMinValue, int theMaxValue);
 
    void print_vector(const std::vector<int>& anArray);
 
    void simple_sort(std::vector<int>& theValues);
}
 

 /*
    Pour les templates, il faut que le template et la fonction générique soient dans le même fichier
    C'est pour cela qu'on met le prototype et la définition de la fonction dans le .hpp
*/

namespace generic
{
    template<typename T>
    struct greater_traits
    {
        public:
            static bool is_greater(T aValue, T anotherValue)
            {
                return aValue > anotherValue;
            }
    };

    template<typename T>
    struct lower_traits
    {
        public:
            static bool is_greater(T aValue, T anotherValue)
            {
                return anotherValue > aValue;
            }
    };
    

    // Création de la fonction générique en donnant un template
    template <typename T, typename genType = int>
    void populate_with_randoms(
        std::vector<T> &theVector,
        int theNumberOfValues, genType theMinValue, genType theMaxValue)
    {
        // Création d'un générateur de nbr aléatoires (seed) puis générateur générant des nombres aléatoires initialisées par une valeur tirée au hasard par le générateur rd.
        static std::random_device rd;            // Variables statiques, initialisées uniquement
        static std::minstd_rand generator(rd()); // lors du premier appel de la fonction et persistant
                                                 // entre deux appels de fonctions.

        std::uniform_int_distribution<> distribution(theMinValue, theMaxValue);
        // Crée une distribution qui prend une valeur générée par un
        // générateur aléatoire et retournant une valeur uniformément
        // distribuée entre theMinValue et theMaxValue.

        for (int i = 0; i < theNumberOfValues; i++)
        {
            theVector.push_back((genType)distribution(generator));  // push_back rajoute une valeur à la fin : équivalent au .append en python
        }
    }

    /*template<>
    void populate_with_randoms(std::vector<std::string>& theVector, int theNumberOfValues, int theMinValue, int theMaxValue)
    {
        // Initialise le générateur de nombres aléatoires
        // et définit la loi de distribution uniforme.
        std::random_device rd; 
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(theMinValue, theMaxValue);
    
        char buffer[20];
    
        int width = theMaxValue - theMinValue;
        for(; 
            theNumberOfValues > 0; 
            theNumberOfValues--)
        {
    
            int randValue = distribution(generator);
            std::sprintf(buffer,"%d",randValue);
            std::string stringValue = buffer;
            theVector.push_back(stringValue);
        }
    }*/

    template<typename T>
    void print_vector(const std::vector<T>& anArray)
    {
        std::cout << "[" << anArray[0];
        for(int i = 1; i<anArray.size(); i++){
            std::cout << "," << anArray[i];
        }
        std::cout << "]" << std::endl;
    }

    template<typename T, typename sortTraits = greater_traits<T>>
    void simple_sort(std::vector<T>& theValues, sortTraits* = NULL)
    {
        for (int i = 0; i<theValues.size(); i++)
        {
            for (int j = i + 1; j< theValues.size(); j++)
            {
                // Compare si les deux elements sont dans le bon ordre.
                if (sortTraits::is_greater(theValues[i], theValues[j]))
                {
                    // Procede a la permutation des deux elements
                    std::swap(theValues[i], theValues[j]);
                }
            }
        }
    }
}
#endif
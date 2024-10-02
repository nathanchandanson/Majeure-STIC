#include"simple_sort.hpp"
#include<iostream>
#include<stdlib.h>
#include <random>
#include <iostream>
 
namespace monomorphic
{

/* theVector est un vecteur non initialisé, et theNumberOfValues est le nombre de données qu'on veut lui rajouter */
void populate_with_randoms(std::vector<int>& theVector,
    int theNumberOfValues, int theMinValue, int theMaxValue)
{ 
    // Création d'un générateur de nbr aléatoires (seed) puis générateur générant des nombres aléatoires initialisées par une valeur tirée au hasard par le générateur rd. 
    static std::random_device rd;               // Variables statiques, initialisées uniquement
    static std::minstd_rand generator(rd());    // lors du premier appel de la fonction et persistant
                                                // entre deux appels de fonctions.
    
    std::uniform_int_distribution<> distribution(theMinValue, theMaxValue);
        // Crée une distribution qui prend une valeur générée par un
        // générateur aléatoire et retournant une valeur uniformément 
        // distribuée entre theMinValue et theMaxValue.
 
    for(int i = 0; i < theNumberOfValues; i++){
        int randomValue = distribution(generator);
            // Une valeur générée entre theMinValue et theMaxValue de 
            // manière équiprobable.

        theVector.push_back(randomValue);   // push_back rajoute une valeur à la fin : équivalent au .append en python
    }
}
 
void print_vector(const std::vector<int>& anArray)
{
    std::cout << "[" << anArray[0];
    for(int i = 1; i<anArray.size(); i++){
        std::cout << "," << anArray[i];
    }
    std::cout << "]" << std::endl;
}
 
void simple_sort(std::vector<int>& theValues)
{
	for (int i = 0; i<theValues.size(); i++)
	{
		for (int j = i + 1; j< theValues.size(); j++)
		{
			// Compare si les deux elements sont dans le bon ordre.
			if (theValues[i] > theValues[j])
			{
				// Procede a la permutation des deux elements
				// int Temp = theValues[i];
				// theValues[i] = theValues[j];
				// theValues[j] = Temp;

                // Sinon utiliser swap
                std::swap(theValues[i], theValues[j]);
			}
		}
	}
}
 
}
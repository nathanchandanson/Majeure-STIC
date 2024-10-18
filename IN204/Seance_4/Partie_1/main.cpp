#include <iostream>
#include <vector>
#include <algorithm>


template <class inputIterator, class T>
inputIterator upper(inputIterator first, inputIterator last, const T& theValue) // Le T& permet de prendre une valeur comme si c'était un poiteur : permet d'éviter la copie -> équivalent à T* thePointer puis après on appelle *thePointer
{
	for (inputIterator it = first; it != last; it++)
	{
		if (*it > theValue)
			return it;
	}
	return last;    // le .end() est exclu, de fait si on est sur le end, ça veut dire qu'on a rien trouvé dans le containeur
}

int testUpper() 
{
	int myints[] = { 10,20,30,30,20,10,10,20 };
	std::vector<int> v(myints, myints + 8);
	std::vector<int>::iterator up = upper(v.begin(), v.end(), 20); 
	std::cout << "Before sorting : first value greater than 20 at position " 
            << (up - v.begin()) /*std::distance(v.begin(), up)*/ << '\n';    // On peut remplacer (up - v.begin()) par std::distance(up, v.begin()) car si on a un itérateur qui ne supporte pas l'opérateur - ça marche quand même
    
    std::sort(v.begin(), v.end());
    up = upper(v.begin(), v.end(), 20); 
    std::cout << "After sorting : first value greater than 20  at position " 
            << (up - v.begin()) /*std::distance(v.begin(), up)*/ << '\n';
	return 0;
}

int main()
{
    testUpper();
    return 0;
}
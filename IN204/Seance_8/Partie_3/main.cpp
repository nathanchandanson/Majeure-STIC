#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////
// Définition des classes
///////////////////////////////////////////////////////////////////////////////////////
class Base
{
public: 
    virtual bool isGreater(const Base&) const = 0; 
        // Retourne true si l'objet courant est plus grand.
    virtual void print() const = 0;
};

class Entier: public Base
{
private:
    int m_value;
public:
    Entier(): m_value(0) {}
    Entier(int theValue): m_value(theValue) {}

    operator int() {return m_value;}

    virtual void print() const override {std::cout << m_value;}
    virtual  bool isGreater(const Base& unEntier) const override
    {
        return m_value > dynamic_cast<const Entier&>(unEntier).m_value;
    }
};


///////////////////////////////////////////////////////////////////////////////////////
// Définition des fonctions
///////////////////////////////////////////////////////////////////////////////////////
std::vector<Base*> create_integer_array(size_t theNumberOfValues)
{
    std::vector<Base*> result;
    result.resize(theNumberOfValues);
    for(int i = 0; i<theNumberOfValues; i++){
        result[i] = new Entier(i);
    }
    return result;
}

void print(std::vector<Base*> anArray)
{
    for(auto it = anArray.begin(); it<anArray.end(); it++){
        (*it)->print();
    }
}

void insertion_sort(std::vector<int>& anArray)
{
	for (int i = 0; i < anArray.size(); i++)
	{
		for (int j = i + 1; j < anArray.size(); j++)
		{
			if (anArray[i] > anArray[j])
				std::swap(anArray[i], anArray[j]);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    return 0;
}
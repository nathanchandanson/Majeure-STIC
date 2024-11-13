#ifndef MATH_HPP
#define MATH_HPP
#include <iostream>

class extended_exception : public std::runtime_error
{
private:
    int catchNumber = 0;
public:
    // Les deux constructeurs s'assurent que c'est forcément une chaine de charactères qui initialise
    explicit extended_exception(const std::string& aMessage): runtime_error(aMessage)   // On met explicit car on veut pas de conversion : on veut un std::string
    {}
    explicit extended_exception(const char* aMessage): runtime_error(aMessage)          // On met explicit car on veut pas de conversion : on veut un char*
    {}

    void catched() {catchNumber++;};
        // Est appelé chaque fois que l’on souhaite indiqué à la classe qu’elle a été
        // capturée. 
    int getCatchNumber() const{return catchNumber;};
        // Retourne le nombre de fois que l’exception a été capturée.
};

class extended_division_by_zero: public extended_exception
{
public:
    extended_division_by_zero(): extended_exception("Division by zero")
    {}
};

class division_by_zero: public std::runtime_error
{
public: 
    division_by_zero(): std::runtime_error("Division by zero")
    {}    
};



double divide(double a, double b) noexcept(false);

#endif
#include "complex.hpp"
#include <cmath>

void Complex::print() const
{
    if(mRealPart != 0.0)
    {
        std::cout << mRealPart;
        if(mImaginaryPart != 0.0)
            std::cout << " + " << mImaginaryPart << " i";
    }
    else if(mImaginaryPart != 0.0)
        std::cout << mImaginaryPart << " i";
    else
        std::cout << "0.0";
    std::cout << std::endl;

}

Complex Complex::createFromCartesian(double x, double y)
{
    return Complex(x,y);
}

Complex Complex::createFromPolar(double rho, double theta)
{
    return Complex(rho*cos(theta), rho*sin(theta));
}

Complex operator + (const Complex& aLeftValue, const Complex& aRightValue)
{
    Complex result = Complex(aLeftValue);
    result.mRealPart += aRightValue.mRealPart;
    result.mImaginaryPart += aRightValue.mImaginaryPart;
    return result;
}

Complex operator + (double aLeftValue, const Complex& aRightValue)
{
    Complex result = Complex(aRightValue);
    result.mRealPart += aLeftValue;
    return result;
}

Complex operator - (const Complex& aLeftValue, const Complex& aRightValue)
{
    Complex result = Complex(aLeftValue);
    result.mRealPart -= aRightValue.mRealPart;
    result.mImaginaryPart -= aRightValue.mImaginaryPart;
    return result;
}

Complex operator - (double aLeftValue, const Complex& aRightValue)
{
    Complex result = Complex(aRightValue);
    result.mRealPart -= aLeftValue;
    return result;
}

Complex& Complex::operator += (const Complex& aRightValue)
{
    this->mRealPart += aRightValue.mRealPart;
    this->mImaginaryPart += aRightValue.mImaginaryPart;
    return *this;
}

Complex& Complex::operator -= (const Complex& aRightValue)
{
    this->mRealPart -= aRightValue.mRealPart;
    this->mImaginaryPart -= aRightValue.mImaginaryPart;
    return *this;
}

Complex operator * (const Complex& aLeftValue, const Complex& aRightValue)
{
    return Complex(aLeftValue.mRealPart*aRightValue.mRealPart - aLeftValue.mImaginaryPart*aRightValue.mImaginaryPart,
                   aLeftValue.mRealPart*aRightValue.mImaginaryPart + aLeftValue.mImaginaryPart*aRightValue.mRealPart);
}

Complex operator / (const Complex& aLeftValue, const Complex& aRightValue)
{
    double squared_norm = aRightValue.mRealPart*aRightValue.mRealPart + aRightValue.mImaginaryPart*aRightValue.mImaginaryPart;
    return Complex(
                (aLeftValue.mRealPart*aRightValue.mRealPart + aLeftValue.mImaginaryPart*aRightValue.mImaginaryPart)/squared_norm,
                (aLeftValue.mImaginaryPart*aRightValue.mRealPart - aLeftValue.mImaginaryPart*aRightValue.mImaginaryPart)/squared_norm);
}

std::ostream& operator <<(std::ostream& theStream, const Complex& aValue)
{
    theStream << aValue.mRealPart;
    theStream << " + i ";
    theStream << aValue.mImaginaryPart;
    theStream << std::endl;
    return theStream;
}

//TODO: todo
std::istream& operator >>(std::istream& theStream, const Complex& aValue)
{
    
    return theStream;
}

// template<class charT, class charTraits>
// std::basic_istream<charT>& operator >>(std::basic_istream<charT, charTraits>&, Complex& aValue);
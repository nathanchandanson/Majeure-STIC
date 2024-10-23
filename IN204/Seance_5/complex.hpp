#ifndef complexHPP
#define complexHPP
#include <iostream>

//TODO: Faire Question 3 Partie_1

class Complex
{
private:
	double mRealPart;
	double mImaginaryPart;
public:
	Complex(double realPart, double imaginaryPart): mRealPart(realPart), mImaginaryPart(imaginaryPart){}
    Complex(float floatValue): mRealPart(floatValue), mImaginaryPart(0){}
    Complex(double doubleValue): mRealPart(doubleValue), mImaginaryPart(0){}
    Complex(int intValue): mRealPart(intValue), mImaginaryPart(0){}

	~Complex()
    {}

    void print() const;
    static Complex createFromCartesian(double x, double y);
    static Complex createFromPolar(double rho, double theta);

    friend Complex operator + (const Complex& aLeftValue, const Complex& aRightValue);
    friend Complex operator + (double aLeftValue, const Complex& aRightValue);
    friend Complex operator - (const Complex& aLeftValue, const Complex& aRightValue);
    friend Complex operator - (double aLeftValue, const Complex& aRightValue);
    Complex& operator += (const Complex& aRightValue);
	Complex& operator -= (const Complex& aRightValue);
    friend Complex operator * (const Complex& aLeftValue, const Complex& aRightValue);
    friend Complex operator / (const Complex& aLeftValue, const Complex& aRightValue);
    friend std::ostream& operator <<(std::ostream& theStream, const Complex& aValue);
    friend std::istream& operator >>(std::istream& theStream, const Complex& aValue);

    static Complex I;
};

#endif
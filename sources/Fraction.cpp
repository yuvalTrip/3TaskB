//
// Created by yuvaltrip on 4/21/23.
//

#include "Fraction.hpp"
#include <cmath> // for round()
#include <typeinfo>

using namespace ariel;
using namespace std;

void Fraction::simplify()
{
    // We will simplify the fraction
    int gcdNum = gcd(numerator, denominator);// Find the GCD
    // Divide each one of the numerator and denominator by the gcd we found
    numerator = numerator/gcdNum;
    denominator = denominator/gcdNum;
};

Fraction::Fraction(int numer, int denom)
{// Two-parameter constructor
// If denominator is 0
    if (denom == 0)
    {
        throw invalid_argument("Denominator can not be zero!");
    }
    // If denominator or numerator are not int
    if ((typeid(numer)) != typeid(int) || (typeid(denom)) != typeid(int))
    {
        throw runtime_error("Numbers need to be int!");
    }

// If initialization correct
    numerator = numer;
    denominator = denom;
    simplify();
    // Add this only because student test 2- case "Fraction comparisons"
    //So the (-) in negative fraction will be on the numerator
    if (denominator<0 )
    {
        numerator=numerator*(-1);
        denominator=denominator*(-1);
    }
}
Fraction::Fraction(float float_num)
//Constructor get float number and turn it to fraction
{
    *this = floatToFraction(float_num);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Empty constructor
Fraction::Fraction()
{//defoltive values (for using in test2- "Input stream operator (>>)"
    numerator = 1;
    denominator = 1;
}


int Fraction::getNumerator() const {
    return numerator;
}
int Fraction::getDenominator() const {
    return denominator;
}
// Function to convert float number to fraction number
Fraction floatToFraction(const float float_num)
{// Global fraction (in use only in case of float-operator-Fraction i.e to operators outstide the Fraction class)
    //0.5555*1000=555.5, +0.5= 556 ->556
    //0.5552*1000=555.2, +0.5=555.7 ->555
    int intF = static_cast<int>(float_num * 1000 + (float_num>0?0.5:-0.5));// if it is negative number we will do -0.5, if it is positive we will do +0.5
    int den = 1000;
    return Fraction(intF, den);
}
// Function to convert float number to fraction number- in use of function of fraction and float
Fraction Fraction::floatToFraction(const float float_num)
{
    int intF = static_cast<int>(float_num * 1000 + (float_num>0?0.5:-0.5));// if it is negative number we will do -0.5, if it is positive we will do +0.5
    int den = 1000;
    return Fraction(intF, den);
}
/// Overload + operator //
// Fraction + Fraction
Fraction Fraction::operator+(const Fraction &other) const
{//the 'const' make sure that the double parameter is treated as a constant
    // and is not modified inside the function.
    // Machane Meshutaf :)
    int num = overflow_plus(overflow_mul(numerator,other.denominator),overflow_mul(other.numerator, denominator));
//    cout<<"first: "<<num<<endl;
    //in start before overflow i did only: int num = (numerator * other.denominator) + (other.numerator * denominator);
    //in start before overflow i did only: int den = denominator * other.denominator;
    int den = overflow_mul(denominator,other.denominator);
//    cout<<"sec: "<<den<<endl;

    return Fraction(num, den);// Simplify

}
// Fraction + Float
Fraction Fraction::operator+(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) + fracF; // Use the function I implemented before of operator +
}

// Float + Fraction( GLOBAL FUNCTION)
Fraction ariel::operator+(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF + frac;
}

/// Overload - operator //
// Fraction - Fraction
Fraction Fraction::operator-(const Fraction &other) const
{
    // Just the same as I did in operator + (but with -)
    int num = overflow_minus(overflow_mul(numerator,other.denominator),overflow_mul(other.numerator,denominator));
    //in start before overflow i did only: int num = (numerator * other.denominator) - (other.numerator * denominator);
    //in start before overflow i did only: int den = denominator * other.denominator;
    int den = overflow_mul(denominator,other.denominator);

//    overflow_minus(num,den);
    return Fraction(num, den);
}
// Fraction - Float
Fraction Fraction::operator-(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) - fracF;// Use the function I implemented before of operator -
}
// Float - Fraction
Fraction ariel::operator-(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF - frac;// Use the function I implemented of Fraction - Fraction
}
/// Overload * operator //
// Fraction * Fraction
Fraction Fraction::operator*(const Fraction &other) const
{
    //in start before overflow i did only:int num = numerator * other.numerator;// Regular multiplication between numerators
    int num = overflow_mul(numerator,other.numerator);// Regular multiplication between numerators

    // Regular multiplication between denominators
    //in start before overflow i did only:int den = denominator * other.denominator;
    int den = overflow_mul(denominator ,other.denominator);

    return Fraction(num, den);// Simplify
}
// Fraction * Float
Fraction Fraction::operator*(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    // No need to simplify! because already done:
    return (*this) * fracF;// Use the function I implemented of Fraction * Fraction
}
// Float * Fraction
Fraction ariel::operator*(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF * frac;// Use the function I implemented of Fraction * Fraction
}
/// Overload / operator //
// Fraction / Fraction
Fraction Fraction::operator/(const Fraction &other) const
{
    //in start before overflow i did only:    int num = numerator * other.denominator;// Cross multiplication
    int num = overflow_mul(numerator ,other.denominator);// Cross multiplication
    //in start before overflow i did only:    int den = denominator * other.numerator;// Cross multiplication
    int den = overflow_mul(denominator , other.numerator);// Cross multiplication
// If denominator is 0 can not do this
    if (den == 0)
    {
        throw runtime_error("Error: Division by zero!");
    }
    return Fraction(num, den);// Simplify
}
// Fraction / Float
Fraction Fraction::operator/(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) / fracF;// Use the function I implemented of Fraction / Fraction
}
// Float / Fraction
Fraction ariel::operator/(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF / frac;// Use the function I implemented of Fraction / Fraction
}

/// Overload == operator //
// Fraction == Fraction
bool Fraction::operator==(const Fraction &other) const
{
    Fraction frac1=Fraction(numerator,denominator); // Simplify first fraction
    //Fraction frac2=Fraction (other.numerator,other.denominator);// Simplify second fraction
    // Compare numerator with numerator and denom with denom AFTER SIMPLIFYING
//    return (frac1.numerator == frac2.numerator) && (frac1.denominator == frac2.denominator);
    // Compare numerator with numerator and denom with denom AFTER SIMPLIFYING
    return (frac1.numerator == other.numerator) && (frac1.denominator == other.denominator);

}
// Fraction == Float
bool Fraction::operator==(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) == fracF;// Use the function I implemented of Fraction == Fraction
}
// Float == Fraction
bool ariel::operator==(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF == frac;// Use the function I implemented of Fraction == Fraction
}

/// Overload > operator //
// Fraction > Fraction
bool Fraction::operator>(const Fraction &other) const
{
    return (numerator * other.denominator) > (other.numerator * denominator); //Haavarat Agafim :)
}
// Fraction > Float
bool Fraction::operator>(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) > fracF;// Use the function I implemented of Fraction > Fraction
}
// Float > Fraction
bool ariel::operator>(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF > frac;// Use the function I implemented of Fraction > Fraction
}

/// Overload < operator //
// Fraction < Fraction
bool Fraction::operator<(const Fraction &other) const
{
    return (numerator * other.denominator) < (other.numerator * denominator);//Haavarat Agafim :)
}
// Fraction < Float
bool Fraction::operator<(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) < fracF;// Use the function I implemented of Fraction < Fraction
}
// Float < Fraction
bool ariel::operator<(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF < frac;// Use the function I implemented of Fraction < Fraction
}
/// Overload >= operator //
// Fraction >= Fraction
bool Fraction::operator>=(const Fraction &other) const
{
    Fraction f1=Fraction(numerator,denominator);// Create first Fraction
    Fraction f2=Fraction(other.numerator,other.denominator);// Create seconed Fraction
    bool ans=(f1>f2 || f1==f2);// Use the operators >,== after I implemented it between Fractions
    return ans;
}
// Fraction >= Float
bool Fraction::operator>=(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) >= fracF;// Use the function I implemented of Fraction >= Fraction
}
// Float >= Fraction
bool ariel::operator>=(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF >= frac;// Use the function I implemented of Fraction >= Fraction
}
/// Overload <= operator //
// Fraction <= Fraction
bool Fraction::operator<=(const Fraction &other) const
{ // The samme as >= !
    Fraction f1=Fraction(numerator,denominator);// Create first Fraction
    Fraction f2=Fraction(other.numerator,other.denominator);// Create seconed Fraction
    bool ans=(f1<f2 || f1==f2);// Use the operators <,== after I implemented it between Fractions
    return ans;
}
// Fraction <= Float
bool Fraction::operator<=(const float float_num)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return (*this) <= fracF;// Use the function I implemented of Fraction <= Fraction
}
// Float <= Fraction
bool ariel::operator<=(const float float_num, const Fraction &frac)
{
    Fraction fracF = floatToFraction(float_num);// Convert float to Fraction
    return fracF <= frac;// Use the function I implemented of Fraction <= Fraction
}

/// Overload ++ operator //
// pre-increment
Fraction &Fraction::operator++()
{
    // by adding the denominator to the numerator we are adding 1
    numerator =numerator+denominator;
    simplify();
    // return reference to the updates object so you can carry on working with it updated
    return *this;
}
// post-increment
Fraction Fraction::operator++(int)
{
    Fraction original = *this;// Create a copy of the original object
    numerator =numerator+denominator;// Increase the value by 1
    simplify();
    return original;// Return the original object before increment

}
/// Overload -- operator //
// pre-decrement
Fraction &Fraction::operator--()
{
    numerator = numerator-denominator;// Decrease value by 1
    simplify();
    return *this;// Return reference to the updates object
    // So I will continue working with the new one
}

// post-decrement
Fraction Fraction::operator--(int)
{
    Fraction original = *this;// Create a copy of the original object
    numerator = numerator- denominator;// Decrease value by 1
    simplify();
    // Return the original object before increment
    return original;
}

///  >> operator //
istream &ariel::operator>>(istream &ins, Fraction &f)
{
    int num, den;
    ins >> num >> den;
    if (ins.fail()) // If input is not 2 integers
    {
        throw runtime_error("Invalid input: expected two integers separated by a space");
    }
    // If there is wrong initialization with denominator 0
    if (den==0)
    {
        throw runtime_error("Invalid input: Denominator can not be 0!");
    }
    // For test case " Input and output operators tests"
    if (den<0 )
    {
        num=num*(-1);
        den=den*(-1);
    }
    f.numerator = num;
    f.denominator = den;
    return ins;
}


///  << operator //
ostream &ariel::operator<<(ostream &outs, const Fraction &frac)
{
    outs << frac.numerator << "/" << frac.denominator; //Fraction form
    return outs;
}

// Function compute the greatest common divisor of two integers
int Fraction::gcd(int num1, int num2) const
{
    if (num2 == 0) //Basic case
    {
        return num1;
    }
    else
    {
        return gcd(num2, num1 % num2);
    }
}

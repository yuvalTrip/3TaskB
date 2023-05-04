#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
using namespace std;
namespace ariel
{
    /* NOTES
     * The 'const' make sure that the parameters I sent are treated as a constant
     and it is not modified inside the function.
     * I used reference and did not create new objects inside the function (
     most of the time) because I want to make it more efficiency
     *
     * */

    class Fraction
    {
        int numerator;
        int denominator;
        static const int min_int=numeric_limits<int>::min();
        static const int max_int= numeric_limits<int>::max();

        static int overflow_minus(int num1, int num2){
            if((num2<0 && num1>max_int+num2) || (num2>0 && num1<min_int+num2))
            {
                throw overflow_error("Minus overflow!");
            }
            return(num1-num2);
        }

        static int overflow_plus(int num1, int num2){
//            cout<<"num1: "<<num1<<endl;
//            cout<<"num2: "<<num2<<endl;
            // Can not write num1+num2>max_int or num1+num2<min_int because it also can be overflow
            if((num2>0 && num1>max_int-num2) || (num2<0 && num1<min_int-num2))
            {
                throw overflow_error("Plus overflow!");
            }
            return(num1+num2);
        }
        static int overflow_mul(int num1, int num2){
//            cout<<"num1: "<<num1<<endl;
//            cout<<"num2: "<<num2<<endl;

            if((num2>0 && num1>max_int/num2) || (num2<0 && num1< max_int/num2))
            {
                throw overflow_error("Multipication overflow!");
            }
            cout<<"num1*num2: "<<num1*num2<<endl;

            return(num1*num2);
        }

    public:
        Fraction(int num, int den); //Constructor get numerator and denominator
        Fraction(float float_num); // Constructor get float num and turn it to fraction
        Fraction(); // Empty constructor
        int getNumerator() const;
        int getDenominator() const;

        Fraction operator+(const Fraction &other) const;
        Fraction operator+(float float_num);

        Fraction operator-(const Fraction &other) const;
        Fraction operator-(float float_num);

        Fraction operator*(const Fraction &other) const;
        Fraction operator*(float float_num);

        Fraction operator/(const Fraction &other) const;
        Fraction operator/(float float_num);

        bool operator==(const Fraction &other) const;
        bool operator==(float float_num);

        bool operator>(const Fraction &other) const;
        bool operator>(float float_num);

        bool operator<(const Fraction &other) const;
        bool operator<(float float_num);

        bool operator>=(const Fraction &other) const;
        bool operator>=(float float_num);

        bool operator<=(const Fraction &other) const;
        bool operator<=(float float_num);

        Fraction &operator++();   // pre-increment
        Fraction operator++(int); // post-increment

        Fraction &operator--();   // pre-decrement
        Fraction operator--(int); // post-decrement

        void simplify() ;
        Fraction floatToFraction(float float_num);
        int gcd(int num1, int num2) const;

        friend ostream &operator<<(std::ostream &outs, const Fraction &frac);
        friend istream &operator>>(std::istream &ins, Fraction &frac);
    };

    Fraction operator+(float float_num, const Fraction &frac);
    Fraction operator-(float float_num, const Fraction &frac);
    Fraction operator*(float float_num, const Fraction &frac);
    Fraction operator/(float float_num, const Fraction &frac);
    bool operator>(float float_num, const Fraction &frac);
    bool operator<(float float_num, const Fraction &frac);
    bool operator==(float float_num, const Fraction &frac);
    bool operator>=(float float_num, const Fraction &frac);
    bool operator<=(float float_num, const Fraction &frac);

}

#endif // FRACTION_HPP
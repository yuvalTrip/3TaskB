/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;


int main() {
    float num=-0.8;
    Fraction fra1=Fraction{3, 4};
    Fraction frac2=Fraction{-16, 15};
    Fraction ans=num/fra1;
    cout << "ans" << ans << endl;
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    Fraction f1(max_int, 1);
    Fraction f4(max_int - 100, max_int);

    Fraction ans2=f1 * f4;
    cout << "ans2: " << ans2 << endl;
    cout << "max_int: " << max_int << endl;
    cout << "max_int*2 : " << max_int*100 << endl;

    Fraction a(5,3), b(14,21);
    cout << "a: " << a << "b: " << b << endl;
    cout << "a+b" << a+b << endl; 
    cout << "a-b" << a-b << endl; 
    cout << "a/b" << a/b << endl; 
    cout << "a*b" << a*b << endl; 
    cout << "2.3*b" << 2.3*b << endl; 
    cout << "a+2.421" << a+2.421 << endl; 
    Fraction c = a+b-1;
    cout << c++ << endl;
    cout << --c << endl;

    cout << "c >=b ? : " << (c >= b) << endl;
    if (a > 1.1) cout << " a is bigger than 1.1" << endl;
    else cout << " a is smaller than 1.1" << endl;


}

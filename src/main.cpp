#include "verifications.h"
#include <iostream>
#include <cmath>


bool Verify::WeierstrassForm( int a, int b ) 
{
    return ( 4 * pow( a, 3.0 ) + 27 * pow( b, 2.0 ) != 0 );
}

bool Verify::FiniteField( [[maybe_unused]] int field )
{
    //TODO: implement to check if field is prime itself
    //      or if field is of the form p ^ k, for prime p and k > 1
    return true;
}

int main(){

    std::cout << "Input your Elliptic Curve in Weirstrass form (y^2 = x^3 + ax + b, with 4a^3 + 27b^2 != 0)\n";

    int a{};
    int b{};
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;

    int field{};
    std::cout << "Enter in your finite field: ";
    std::cin >> field;

    if (Verify::WeierstrassForm( a, b )) std::cout << "form good\n";
    if (Verify::FiniteField( field )) std::cout << "field good\n";
    
    
return 0;
}


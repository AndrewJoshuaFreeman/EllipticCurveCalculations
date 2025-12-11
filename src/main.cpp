#include <iostream>
#include <cmath>

bool verifyWeirstrass([[maybe_unused]] int a, [[maybe_unused]] int b ){return true;}

bool verifyFiniteField( [[maybe_unused]] int field ){return true;}

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

    verifyWeirstrass( a, b );
    verifyFiniteField( field );
    
    
return 0;
}


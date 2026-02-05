#include <iostream>
#include "../Include/Rootfinding.hpp"

using namespace std; // this tells compiler cout means std::cout

int main()
{
    double a = 0.5; // left interval end
    double b = 1.0; // Right interval end
    double tolerance = 0.0001; // stoping conditions

    cout << "Bisection Method for f(x) = 4x^3 - 3x\n";
    cout << "Initial Interval: [0.5 , 1]\n";
    cout << "Tolerance: " << tolerance << "\n\n"; // prints tollerance value

    bisectionMethod(a, b, tolerance); // calls the fun bisection pass three parameters left end  right end and stoping condition

    return 0;
}

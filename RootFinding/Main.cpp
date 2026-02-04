#include <iostream>
#include "include/RootFinding.hpp"

using namespace std;

int main()
{
    double a = 0.5;
    double b = 1.0;
    double tolerance = 0.0001;

    cout << "Bisection Method for f(x) = 4x^3 - 3x\n";
    cout << "Initial Interval: [0.5 , 1]\n\n";

    bisectionMethod(a, b, tolerance);

    return 0;
}

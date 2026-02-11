#include <iostream>
#include "../Include/RootFinding.hpp"

using namespace std;

int main()
{
    double tolerance = 0.0001;   // stopping condition
    int maxIter = 100;           // safety limit

    // creating objects of each class
    Bisection b(0.5, 1.0, tolerance, maxIter);
    NewtonRaphson n(0.7, tolerance, maxIter);
    FixedPoint f(0.7, tolerance, maxIter);

    // calling solve function for each object
    b.solve();
    n.solve();
    f.solve();

    return 0;
}

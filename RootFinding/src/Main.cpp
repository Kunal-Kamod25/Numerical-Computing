#include <iostream>
#include "../Include/Rootfinding.hpp"

using namespace std;

int main()
{
    double tolerance = 0.0001;   // stopping condition
    int maxIter = 100;           // safety limit

    // creating objects of each class
    Bisection Bisection(0.5, 1.0, tolerance, maxIter);
    NewtonRaphson Newton_Raphson(0.7, tolerance, maxIter);
    FixedPoint Fixed_Point(0.7, tolerance, maxIter);

    // calling solve function for each object
    Bisection.solve();
    Newton_Raphson.solve();
    Fixed_Point.solve();

    return 0;
}

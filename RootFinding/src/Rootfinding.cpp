#include <iostream>
#include <cmath>
#include "../Include/Rootfinding.hpp"
#include "../Include/Utils.hpp"

using namespace std;

// constructor of base class
RootFinding::RootFinding(double tol, int maxIter)
{
    tolerance = tol;          // set stopping condition
    maxIteration = maxIter;   // set maximum iterations
}

// Bisection Method 
Bisection::Bisection(double left, double right, double tol, int maxIter)
    : RootFinding(tol, maxIter)   // calling parent constructor
{
    a = left;     // set left interval
    b = right;    // set right interval
}

void Bisection::solve()
{
    double mid;       // to store midpoint
    int iteration = 1;

    // loop until max iterations
    while (iteration <= maxIteration)
    {
        mid = (a + b) / 2;   // formula for midpoint

        // if result is accurate enough, stop
        if (abs(function(mid)) < tolerance)
            break;

        // check which side root exists
        if (function(a) * function(mid) < 0)
            b = mid;
        else
            a = mid;

        iteration++;
    }
    cout << "Bisection Root = " << mid << endl;
}


// Newton Raphson Method
NewtonRaphson::NewtonRaphson(double initialGuess, double tol, int maxIter)
    : RootFinding(tol, maxIter)
{
    x0 = initialGuess;   // set starting bvalue
}

void NewtonRaphson::solve()
{
    double x1;
    int iteration = 1;

    while (iteration <= maxIteration)
    {
        // Newton formulab
        x1 = x0 - function(x0) / derivative(x0);

        // stop if accurate
        if (abs(function(x1)) < tolerance)
            break;

        x0 = x1;   // update value
        iteration++;
    }

    cout << "Newton Raphson Root = " << x1 << endl;
}


//Fixed Point Method

FixedPoint::FixedPoint(double initialGuess, double tol, int maxIter)
    : RootFinding(tol, maxIter)
{
    x0 = initialGuess;
}

void FixedPoint::solve()
{
    double x1;
    int iteration = 1;

    while (iteration <= maxIteration)
    {
        x1 = g(x0);   // fixed point formula

        // stop if difference small
        if (abs(x1 - x0) < tolerance)
            break;

        x0 = x1;
        iteration++;
    }
    cout << "Fixed Point Root = " << x1 << endl;
}
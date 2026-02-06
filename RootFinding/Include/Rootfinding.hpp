// Declares Rootfinding algorithms
// -Function declarations

// Header guard + fun declaration
#ifndef ROOTFINDING_HPP // not define yet
#define ROOTFINDING_HPP

class bisectionMethod{
public:
    // data members
    double a;
    double b;
    double tolerance;
    int iteration;

    // constructor
    bisectionMethod(); // Deafult
    bisectionMethod(double a, double b, double tolerance, int iteration);// Parameterized


};

#endif

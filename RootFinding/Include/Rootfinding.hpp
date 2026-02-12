#ifndef ROOTFINDING_HPP      // this avoids including file multiple times
#define ROOTFINDING_HPP

// abstract base class (parent class)
class RootFinding
{
    protected:
    double tolerance;        // stopping condition
    int maxIteration;        // safety limit so loop does not run forever

    public:
    // constructor to set tolerance and max iterations
    RootFinding(double tol, int maxIter);

    // pure virtual function 
    virtual void solve() = 0;// line 16 33 // Virtual function is a Member fun // no implementation in the base class
}; 


// Bisection Class

// Bisection inherits from RootFinding
class Bisection : public RootFinding  // sir this is a Is-A relationship (bisection Is-A rootfinding method)
{
    private:
    double a;    // left interval
    double b;    // right interval

    public:
    // constructor
    Bisection(double left, double right, double tol, int maxIter);
    // override solve function
    void solve();
};


// Newton-Raphson class
class NewtonRaphson : public RootFinding // newtonraphson Is-A rootfinding method
{
    private:
    double x0;   // initial guess

    public:
    NewtonRaphson(double initialGuess, double tol, int maxIter);
    void solve();
};


// Fixed Point Class
class FixedPoint : public RootFinding 
{
    private:
    double x0;   // initial guess

    public:
    FixedPoint(double initialGuess, double tol, int maxIter);
    void solve();
};

#endif   // ROOTFINDING_HPP

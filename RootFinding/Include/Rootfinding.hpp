#ifndef ROOTFINDING_HPP      // this avoids including file multiple times
#define ROOTFINDING_HPP

// base class (parent class)
class RootFinding
{
protected:
    double tolerance;        // stopping condition
    int maxIteration;        // safety limit so loop does not run forever

public:
    // constructor to set tolerance and max iterations
    RootFinding(double tol, int maxIter);

    // pure virtual function (forces child classes to write their own solve function)
    virtual void solve() = 0;
};


// ---------------- Bisection Class ----------------

// Bisection inherits from RootFinding
class Bisection : public RootFinding
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


// ---------------- Newton Raphson Class ----------------

class NewtonRaphson : public RootFinding
{
private:
    double x0;   // initial guess

public:
    NewtonRaphson(double initialGuess, double tol, int maxIter);

    void solve();
};


// ---------------- Fixed Point Class ----------------

class FixedPoint : public RootFinding
{
private:
    double x0;   // initial guess

public:
    FixedPoint(double initialGuess, double tol, int maxIter);

    void solve();
};

#endif

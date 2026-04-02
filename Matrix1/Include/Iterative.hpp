#ifndef ITERATIVE_HPP
#define ITERATIVE_HPP

#include "SLE.hpp"

// ============================================================
// Iterative Class: Base for Iterative Methods like Jacobi & GS
// ============================================================
// We inherit from SLE because iterative methods also solve 
// linear systems, but they do it by guessing and refining!
class Iterative : public SLE
{
protected:
    int maxIterations;
    long double tolerance;

public:
    Iterative() : SLE(), maxIterations(1000), tolerance(1e-10) {}
    Iterative(int r, int c) : SLE(r, c), maxIterations(1000), tolerance(1e-10) {}
    Iterative(const Matrix &other) : SLE(other), maxIterations(1000), tolerance(1e-10) {}

    // Setters for user to control the solver
    void setMaxIterations(int iter) { maxIterations = iter; }
    void setTolerance(long double tol) { tolerance = tol; }

    // Prepare a matrix once before creating Jacobi/Gauss-Seidel objects
    static void ensureDiagonallyDominant(Matrix &system);

    // Optional instance helper for the current object
    void ensureDiagonallyDominant();

    // This method will be implemented by Jacobi and Gauss-Seidel
    virtual std::vector<long double> solveIterative() = 0;
};

// ============================================================
// Jacobi Class: The "Simple & Parallel" Iterative Method
// ============================================================
class Jacobi : public Iterative
{
public:
    Jacobi() : Iterative() {}
    Jacobi(int r, int c) : Iterative(r, c) {}
    Jacobi(const Matrix &other) : Iterative(other) {}

    // The Jacobi algorithm uses the PREVIOUS step's values to 
    // calculate ALL new values at once.
    std::vector<long double> solveIterative() override;
};

// ============================================================
// GaussSeidel Class: The "Faster & Immediate" Iterative Method
// ============================================================
class GaussSeidel : public Iterative
{
public:
    GaussSeidel() : Iterative() {}
    GaussSeidel(int r, int c) : Iterative(r, c) {}
    GaussSeidel(const Matrix &other) : Iterative(other) {}

    // Gauss-Seidel uses the LATEST values as soon as they are
    // calculated, which usually makes it converge much faster!
    std::vector<long double> solveIterative() override;
};

#endif

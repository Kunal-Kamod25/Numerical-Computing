#ifndef GAUSS_ELIMINATION_HPP
#define GAUSS_ELIMINATION_HPP

#include "SLE.hpp"

// Class for Gaussian Elimination algorithms

class GaussianElimination : public SLE
{
public:
    GaussianElimination() : SLE() {}
    GaussianElimination(int r, int c) : SLE(r, c) {}
    GaussianElimination(const Matrix &other) : SLE(other) {}
    GaussianElimination(const SLE &other) : SLE(other) {}

    // Pivoting
    void basicPivoting(int currIndex);

    // Convert matrix to upper triangular form
    virtual void upperTriangularWithoutPivot();
    virtual void upperTriangularWithPivot();
};

#endif
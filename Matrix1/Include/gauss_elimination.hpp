#ifndef GAUSS_ELIMINATION_HPP
#define GAUSS_ELIMINATION_HPP

#include "Matrix.hpp"

// Class for Gaussian Elimination algorithms

class GaussianElimination : public Matrix
{
public:
    GaussianElimination() : Matrix() {}
    GaussianElimination(int r, int c) : Matrix(r, c) {}
    GaussianElimination(const Matrix &other) : Matrix(other) {}

    // Pivoting
    void basicPivoting(int currIndex);

    // Convert matrix to upper triangular form
    virtual void upperTriangularWithoutPivot();
    virtual void upperTriangularWithPivot();
};

#endif
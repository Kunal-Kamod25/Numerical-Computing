#ifndef LU_HPP
#define LU_HPP

#include "Matrix.hpp"
#include <vector>

/*
    LU Decomposition Class

    This class supports three LU based methods:

        1. Doolittle
        2. Crout
        3. Cholesky

    Additionally, when a zero pivot is detected
    we automatically perform partial pivoting
    to avoid division by zero.

    The permutation vector P stores row swaps.
*/

class LU : public Matrix
{
public:

    Matrix L;        // Lower triangular matrix
    Matrix U;        // Upper triangular matrix

    std::vector<int> P;   // Permutation vector (for pivoting)

    LU(int n);
    LU(const Matrix &A);

    // LU Methods
    void doolittle(const Matrix &A);
    void crout(const Matrix &A);
    void cholesky(const Matrix &A);

    // Solve Ax = B
    std::vector<long double> solve(const Matrix &B);
};

#endif
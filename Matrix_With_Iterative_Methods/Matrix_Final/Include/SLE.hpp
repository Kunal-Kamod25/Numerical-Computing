#ifndef SLE_HPP
#define SLE_HPP

#include "Matrix.hpp"
#include <vector>

// ===========================================
// Class for solving Systems of Linear Equations
// ===========================================
class SLE : public Matrix
{
public:
    SLE() : Matrix() {}
    SLE(int r, int c) : Matrix(r, c) {}
    SLE(const Matrix &other) : Matrix(other) {}

    // Solver types - ORIGINAL: GAUSSIAN and LU_METHOD
    //                NEW: JACOBI and GAUSS_SEIDEL (iterative methods)
    enum SolverType { 
        GAUSSIAN,      // Direct: Gaussian Elimination (original)
        LU_METHOD,     // Direct: LU Decomposition (original)
        JACOBI,        // NEW: Iterative Jacobi method
        GAUSS_SEIDEL   // NEW: Iterative Gauss-Seidel method
    };
    
    enum LUMethod { DOOLITTLE, CROUT, CHOLESKY };

    // Back substitution to vector
    std::vector<long double> backSubstitutionToVec() const;

    // Solve system - UPDATED to support iterative methods
    std::vector<long double> solve(
        SolverType method = GAUSSIAN, 
        LUMethod lu_m = DOOLITTLE,
        int max_iterations = 1000,      // For iterative methods
        long double tolerance = 1e-10   // For iterative methods
    );
    
    // Original methods (kept unchanged)
    Matrix solveWithPivot();
    Matrix solveWithoutPivot();
};

#endif
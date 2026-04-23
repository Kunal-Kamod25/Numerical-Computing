#ifndef SLE_HPP
#define SLE_HPP

#include "gauss_elimination.hpp"

// ===========================================
// Class for solving Systems of Linear Equations
// ===========================================
class SLE : public GaussianElimination
{
public:
    SLE() : GaussianElimination() {}
    SLE(int r, int c) : GaussianElimination(r, c) {}
    SLE(const Matrix &other) : GaussianElimination(other) {}

    enum SolverType { GAUSSIAN, LU_METHOD };
    enum LUMethod { DOOLITTLE, CROUT, CHOLESKY };

    // Back substitution to vector
    std::vector<long double> backSubstitutionToVec() const;

    // Solve system
    std::vector<long double> solve(SolverType method = GAUSSIAN, LUMethod lu_m = DOOLITTLE);
    
    // Existing methods (updated to use vector if needed, or kept for compatibility)
    Matrix solveWithPivot();
    Matrix solveWithoutPivot();

    // Save solution
};

#endif
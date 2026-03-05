#ifndef SLE_HPP
#define SLE_HPP

// =====================================================
// Solve Linear Equation functions
// =====================================================

// Back substitution
Matrix backSubstitution() const;

Matrix backsubstitution2() const;

// Solve system
Matrix solveWithPivot();

Matrix solveWithoutPivot();

// Save solution
void saveSolution(const std::string &filename) const;

#endif
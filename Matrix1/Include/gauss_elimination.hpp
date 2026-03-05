#ifndef GAUSS_ELIMINATION_HPP
#define GAUSS_ELIMINATION_HPP

// =====================================================
// Gaussian Elimination member functions
// =====================================================

// Pivoting
void basicPivoting(int currIndex);

// Convert matrix to upper triangular form
void upperTriangularWithoutPivot();

void upperTriangularWithPivot();

#endif
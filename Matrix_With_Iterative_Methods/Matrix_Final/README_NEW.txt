===============================================
  MATRIX LIBRARY - WITH ITERATIVE SOLVERS
===============================================

WHAT'S INCLUDED:
===============================================

ORIGINAL METHODS (Unchanged):
  ✓ Gaussian Elimination
  ✓ LU Decomposition (Doolittle)
  ✓ LU Decomposition (Crout)
  ✓ LU Decomposition (Cholesky)

NEW METHODS (Added):
  ✓ Jacobi Iterative Method
  ✓ Gauss-Seidel Iterative Method


QUICK START:
===============================================

1. COMPILE:
   make

2. RUN SIMPLE DEMO:
   ./simple_demo

3. RUN FULL TEST:
   ./test_methods


HOW TO USE THE NEW METHODS:
===============================================

// NEW: Jacobi Method
auto sol = system.solve(SLE::JACOBI, SLE::DOOLITTLE, 1000, 1e-10);

// NEW: Gauss-Seidel Method  
auto sol = system.solve(SLE::GAUSS_SEIDEL, SLE::DOOLITTLE, 1000, 1e-10);

// ORIGINAL methods still work exactly as before!
auto sol = system.solve(SLE::GAUSSIAN);
auto sol = system.solve(SLE::LU_METHOD, SLE::DOOLITTLE);


WHAT WAS CHANGED:
===============================================

✓ Added IterativeSolver.hpp (NEW file)
✓ Updated SLE.hpp (added 2 enum values)
✓ Updated Matrix_Algorithms.cpp (added 2 cases)
✓ ALL OTHER FILES UNCHANGED

Your original code is 100% safe!


ENJOY YOUR ENHANCED MATRIX LIBRARY!
===============================================

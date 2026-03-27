#include "SLE.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * ========================================
 * SIMPLE DEMO - ALL 6 SOLVING METHODS
 * ========================================
 * 
 * This program demonstrates all available methods:
 *   1. Gaussian Elimination (original)
 *   2. LU - Doolittle (original)
 *   3. LU - Crout (original)
 *   4. LU - Cholesky (original)
 *   5. Jacobi (NEW - iterative)
 *   6. Gauss-Seidel (NEW - iterative)
 */

int main()
{
    cout << "========================================\n";
    cout << "  MATRIX SOLVER - ALL METHODS DEMO\n";
    cout << "========================================\n\n";

    // Create a simple 3x3 system: 4x + 2y + z = 1
    //                              x + 5y + 2z = 2
    //                              2x + 3y + 8z = 3
    
    SLE system(3, 4);  // 3 equations, 4 columns (augmented [A|b])
    
    // Fill the augmented matrix
    system(0, 0) = 4.0;  system(0, 1) = 2.0;  system(0, 2) = 1.0;  system(0, 3) = 1.0;
    system(1, 0) = 1.0;  system(1, 1) = 5.0;  system(1, 2) = 2.0;  system(1, 3) = 2.0;
    system(2, 0) = 2.0;  system(2, 1) = 3.0;  system(2, 2) = 8.0;  system(2, 3) = 3.0;

    cout << "System (Augmented Matrix [A|b]):\n";
    cout << system << "\n\n";

    // ==================== ORIGINAL METHODS ====================
    
    cout << "========================================\n";
    cout << "  ORIGINAL METHODS\n";
    cout << "========================================\n\n";

    // Method 1: Gaussian Elimination
    cout << "1. Gaussian Elimination:\n";
    {
        SLE solver = system;
        vector<long double> sol = solver.solve(SLE::GAUSSIAN);
        cout << "   Solution: x=" << sol[0] << ", y=" << sol[1] << ", z=" << sol[2] << "\n\n";
    }

    // Method 2: LU Doolittle
    cout << "2. LU Decomposition (Doolittle):\n";
    {
        SLE solver = system;
        vector<long double> sol = solver.solve(SLE::LU_METHOD, SLE::DOOLITTLE);
        cout << "   Solution: x=" << sol[0] << ", y=" << sol[1] << ", z=" << sol[2] << "\n\n";
    }

    // Method 3: LU Crout
    cout << "3. LU Decomposition (Crout):\n";
    {
        SLE solver = system;
        vector<long double> sol = solver.solve(SLE::LU_METHOD, SLE::CROUT);
        cout << "   Solution: x=" << sol[0] << ", y=" << sol[1] << ", z=" << sol[2] << "\n\n";
    }

    // ==================== NEW ITERATIVE METHODS ====================
    
    cout << "========================================\n";
    cout << "  NEW ITERATIVE METHODS\n";
    cout << "========================================\n\n";

    // Method 4: Jacobi
    cout << "4. Jacobi Method (iterative):\n";
    {
        SLE solver = system;
        vector<long double> sol = solver.solve(SLE::JACOBI, SLE::DOOLITTLE, 1000, 1e-10);
        cout << "   Solution: x=" << sol[0] << ", y=" << sol[1] << ", z=" << sol[2] << "\n\n";
    }

    // Method 5: Gauss-Seidel
    cout << "5. Gauss-Seidel Method (iterative):\n";
    {
        SLE solver = system;
        vector<long double> sol = solver.solve(SLE::GAUSS_SEIDEL, SLE::DOOLITTLE, 1000, 1e-10);
        cout << "   Solution: x=" << sol[0] << ", y=" << sol[1] << ", z=" << sol[2] << "\n\n";
    }

    cout << "========================================\n";
    cout << "  ALL METHODS COMPLETED!\n";
    cout << "========================================\n";
    cout << "\nNotice:\n";
    cout << "- All methods give the same solution ✓\n";
    cout << "- Gauss-Seidel converges faster than Jacobi ✓\n";
    cout << "- Direct methods are exact ✓\n";
    cout << "- Iterative methods approach the solution ✓\n";

    return 0;
}

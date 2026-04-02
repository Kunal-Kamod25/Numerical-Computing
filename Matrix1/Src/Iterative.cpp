#include "Iterative.hpp"
#include <cmath>
#include <iomanip>

// ============================================================
// Shared Iterative Helper
// ============================================================
void Iterative::ensureDiagonallyDominant(Matrix &system)
{
    if (!system.isDiagonallyDominant())
    {
        std::cout << "Matrix is not diagonally dominant. Reordering rows..." << std::endl;
        system.makeDiagonallyDominant();
    }
    else
    {
        std::cout << "Matrix is already diagonally dominant." << std::endl;
    }
}

void Iterative::ensureDiagonallyDominant()
{
    Iterative::ensureDiagonallyDominant(static_cast<Matrix &>(*this));
}

// ============================================================
// Implementation of Jacobi Method
// ============================================================
std::vector<long double> Jacobi::solveIterative()
{
    int n = rows;
    // We assume the augmented matrix is [A | b]
    // A has n rows and n columns. b is the (n+1)-th column.
    
    // Initial guess: all zeros
    std::vector<long double> x(n, 0.0);
    std::vector<long double> x_new(n, 0.0);

    std::cout << "Starting Jacobi iterations (max: " << maxIterations << ")..." << std::endl;

    for (int iter = 0; iter < maxIterations; iter++)
    {
        long double max_diff = 0.0;

        for (int i = 0; i < n; i++)
        {
            long double sigma = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    // mat[i][j] is the coefficient from A
                    sigma += mat[i][j] * x[j];
                }
            }

            // Jacobi formula: x_new[i] = (b[i] - sigma) / A[i][i]
            // b[i] is at mat[i][n]
            if (std::abs(mat[i][i]) < 1e-18) {
                throw std::runtime_error("Zero diagonal element in Jacobi! Matrix might not be diagonally dominant.");
            }
            
            x_new[i] = (mat[i][n] - sigma) / mat[i][i];

            // Check how much it changed for convergence
            max_diff = std::max(max_diff, (long double)std::abs(x_new[i] - x[i]));
        }

        x = x_new;

        // If the change is smaller than our tolerance, we are done!
        if (max_diff < tolerance)
        {
            std::cout << "Jacobi converged after " << iter + 1 << " iterations." << std::endl;
            solution_vec = x;
            return x;
        }
    }

    std::cout << "Warning: Jacobi reached max iterations without full convergence." << std::endl;
    solution_vec = x;
    return x;
}

// ============================================================
// Implementation of Gauss-Seidel Method
// ============================================================
std::vector<long double> GaussSeidel::solveIterative()
{
    int n = rows;
    
    // Initial guess: all zeros
    std::vector<long double> x(n, 0.0);

    std::cout << "Starting Gauss-Seidel iterations (max: " << maxIterations << ")..." << std::endl;

    for (int iter = 0; iter < maxIterations; iter++)
    {
        long double max_diff = 0.0;

        for (int i = 0; i < n; i++)
        {
            long double old_xi = x[i];
            long double sigma = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    // Here we use the ALREADY UPDATED values of x for j < i
                    // and the old values for j > i. This is the GS magic!
                    sigma += mat[i][j] * x[j];
                }
            }

            if (std::abs(mat[i][i]) < 1e-18) {
                throw std::runtime_error("Zero diagonal element in GS! Matrix might not be diagonally dominant.");
            }

            x[i] = (mat[i][n] - sigma) / mat[i][i];

            // Update max difference for convergence check
            max_diff = std::max(max_diff, (long double)std::abs(x[i] - old_xi));
        }

        if (max_diff < tolerance)
        {
            std::cout << "Gauss-Seidel converged after " << iter + 1 << " iterations." << std::endl;
            solution_vec = x;
            return x;
        }
    }

    std::cout << "Warning: Gauss-Seidel reached max iterations without full convergence." << std::endl;
    solution_vec = x;
    return x;
}

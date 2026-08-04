#ifndef ITERATIVE_SOLVER_HPP
#define ITERATIVE_SOLVER_HPP

#include "SLE.hpp"
#include <vector>

// LINEAR SYSTEM BASE CLASS
//  * Base class for all linear system solvers.
//  * Provides common functionality for solving Ax = b
 
class LinearSystem : public SLE
{
protected:
    std::vector<long double> b_vec;     // Right-hand side vector (extracted from augmented matrix)
    int max_iterations;                  // Maximum number of iterations for convergence
    long double tolerance;               // Convergence tolerance (stopping criteria)
    
public:
    // Constructors
    LinearSystem();
    LinearSystem(int n, int cols);
    LinearSystem(const Matrix &other);
    LinearSystem(const SLE &other);
    
    // Setters for solver parameters
    void setMaxIterations(int max_iter);
    void setTolerance(long double tol);
    
    // Extract b vector from augmented matrix [A|b]
    void extractRHS();
    
    // Pure virtual solve method - must be implemented by derived classes
    virtual std::vector<long double> solve() = 0;
    
    // Utility: Calculate residual norm ||Ax - b||
    long double residualNorm(const std::vector<long double>& x) const;
    
    virtual ~LinearSystem();
};


/**
 ITERATIVE SOLVER BASE CLASS
 * Base class for iterative methods (Jacobi, Gauss-Seidel, SOR, etc.)
 * Provides common convergence checking and initialization
 */
class IterativeSolver : public LinearSystem
{
protected:
    std::vector<long double> x_current;  // Current solution estimate
    std::vector<long double> x_previous; // Previous iteration solution
    int iteration_count;                 // Track number of iterations performed
    
    // Check if diagonal is dominant (required for convergence guarantee)
    bool checkDiagonalDominance() const;
    
    // Check convergence: ||x_current - x_previous|| < tolerance
    bool hasConverged() const;
    
    // Initialize solution vector (can use initial guess or zeros)
    void initializeSolution(const std::vector<long double>* initial_guess = nullptr);
    
public:
    // Constructors
    IterativeSolver();
    IterativeSolver(int n, int cols);
    IterativeSolver(const Matrix &other);
    
    // Get iteration count after solving
    int getIterationCount() const;
    
    // Pure virtual method for single iteration step (implemented by derived classes)
    virtual void performIteration() = 0;
    
    // Common solve framework for all iterative methods
    std::vector<long double> solve() override;
    
    virtual ~IterativeSolver();
};

/**
 * JACOBI METHOD
 * Iterative solver using Jacobi method:
 * All components of x are updated simultaneously using values from previous iteration
 */
class JacobiSolver : public IterativeSolver
{
public:
    // Constructors
    JacobiSolver();
    JacobiSolver(int n, int cols);
    JacobiSolver(const Matrix &other);
    
    // Perform one Jacobi iteration
    void performIteration() override;
};

/**
 * GAUSS-SEIDEL METHOD
 * Iterative solver using Gauss-Seidel method:
 * Components are updated sequentially, using latest available values
 * Generally converges faster than Jacobi
 */
class GaussSeidelSolver : public IterativeSolver
{
public:
    // Constructors
    GaussSeidelSolver();
    GaussSeidelSolver(int n, int cols);
    GaussSeidelSolver(const Matrix &other);
    
    // Perform one Gauss-Seidel iteration
    void performIteration() override;
};

#endif // ITERATIVE_SOLVER_HPP

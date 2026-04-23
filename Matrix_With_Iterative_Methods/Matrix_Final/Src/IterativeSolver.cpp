#include "../Include/IterativeSolver.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

// ===============================================
// LINEAR SYSTEM BASE CLASS
// ===============================================

LinearSystem::LinearSystem() : SLE(), max_iterations(1000), tolerance(1e-10) {}
LinearSystem::LinearSystem(int n, int cols) : SLE(n, cols), max_iterations(1000), tolerance(1e-10) {}
LinearSystem::LinearSystem(const Matrix &other) : SLE(other), max_iterations(1000), tolerance(1e-10) {}
LinearSystem::LinearSystem(const SLE &other) : SLE(other), max_iterations(1000), tolerance(1e-10) {}

void LinearSystem::setMaxIterations(int max_iter) { max_iterations = max_iter; }
void LinearSystem::setTolerance(long double tol) { tolerance = tol; }

void LinearSystem::extractRHS() {
    b_vec.resize(rows);
    for (int i = 0; i < rows; i++) {
        b_vec[i] = mat[i][cols - 1];  // Last column is RHS
    }
}

long double LinearSystem::residualNorm(const std::vector<long double>& x) const {
    long double norm = 0.0;
    for (int i = 0; i < rows; i++) {
        long double sum = 0.0;
        for (int j = 0; j < rows; j++) {
            sum += mat[i][j] * x[j];
        }
        long double diff = sum - b_vec[i];
        norm += diff * diff;
    }
    return sqrtl(norm);
}

LinearSystem::~LinearSystem() {}

// ===============================================
// ITERATIVE SOLVER BASE CLASS
// ===============================================

IterativeSolver::IterativeSolver() : LinearSystem(), iteration_count(0) {}
IterativeSolver::IterativeSolver(int n, int cols) : LinearSystem(n, cols), iteration_count(0) {}
IterativeSolver::IterativeSolver(const Matrix &other) : LinearSystem(other), iteration_count(0) {}

bool IterativeSolver::checkDiagonalDominance() const {
    for (int i = 0; i < rows; i++) {
        long double diag = fabsl(mat[i][i]);
        long double sum = 0.0;
        for (int j = 0; j < rows; j++) {
            if (i != j) sum += fabsl(mat[i][j]);
        }
        if (diag <= sum) return false;  // Not diagonally dominant
    }
    return true;
}

bool IterativeSolver::hasConverged() const {
    long double diff_norm = 0.0;
    for (int i = 0; i < rows; i++) {
        long double diff = x_current[i] - x_previous[i];
        diff_norm += diff * diff;
    }
    return sqrtl(diff_norm) < tolerance;
}

void IterativeSolver::initializeSolution(const std::vector<long double>* initial_guess) {
    x_current.resize(rows);
    x_previous.resize(rows);
    
    if (initial_guess && initial_guess->size() == (size_t)rows) {
        // Use provided initial guess
        x_current = *initial_guess;
    } else {
        // Default: start with zeros
        for (int i = 0; i < rows; i++) {
            x_current[i] = 0.0;
        }
    }
    x_previous = x_current;
    iteration_count = 0;
}

int IterativeSolver::getIterationCount() const { return iteration_count; }

std::vector<long double> IterativeSolver::solve() {
    // Step 1: Check and attempt to make matrix diagonally dominant if needed
    if (!checkDiagonalDominance()) {
        if (!makeDiagonallyDominant()) {
            std::cerr << "Warning: Matrix is NOT diagonally dominant, solver may not converge!\n";
        } else {
            std::cout << "Matrix was automatically made diagonally dominant via row swapping.\n";
        }
    }
    
    // Step 2: Extract RHS from augmented matrix (AFTER any row swaps)
    extractRHS();
    
    // Step 3: Initialize solution vector
    initializeSolution();
    
    // Step 4: Iterative loop
    for (iteration_count = 0; iteration_count < max_iterations; iteration_count++) {
        x_previous = x_current;  // Save previous solution
        
        performIteration();       // Perform one iteration (method-specific)
        
        // Check for convergence
        if (hasConverged()) {
            solution_vec = x_current;
            return solution_vec;
        }
    }
    
    // Maximum iterations reached without convergence
    std::cerr << "Warning: Maximum iterations (" << max_iterations 
              << ") reached. Solution may not have converged.\n";
    std::cerr << "Final residual norm: " << residualNorm(x_current) << "\n";
    
    solution_vec = x_current;
    return solution_vec;
}

IterativeSolver::~IterativeSolver() {}

// ===============================================
// JACOBI METHOD
// ===============================================

JacobiSolver::JacobiSolver() : IterativeSolver() {}
JacobiSolver::JacobiSolver(int n, int cols) : IterativeSolver(n, cols) {}
JacobiSolver::JacobiSolver(const Matrix &other) : IterativeSolver(other) {}

void JacobiSolver::performIteration() {
    for (int i = 0; i < rows; i++) {
        // Check for zero diagonal element
        if (fabsl(mat[i][i]) < 1e-18) {
            throw std::runtime_error("Zero diagonal element in Jacobi method at row " + std::to_string(i));
        }
        
        // Calculate: x_i = (b_i - Σ(a_ij * x_j)) / a_ii
        long double sum = 0.0;
        for (int j = 0; j < rows; j++) {
            if (i != j) {
                sum += mat[i][j] * x_previous[j];  // Use OLD values
            }
        }
        x_current[i] = (b_vec[i] - sum) / mat[i][i];
    }
}

// ===============================================
// GAUSS-SEIDEL METHOD
// ===============================================

GaussSeidelSolver::GaussSeidelSolver() : IterativeSolver() {}
GaussSeidelSolver::GaussSeidelSolver(int n, int cols) : IterativeSolver(n, cols) {}
GaussSeidelSolver::GaussSeidelSolver(const Matrix &other) : IterativeSolver(other) {}

void GaussSeidelSolver::performIteration() {
    for (int i = 0; i < rows; i++) {
        // Check for zero diagonal element
        if (fabsl(mat[i][i]) < 1e-18) {
            throw std::runtime_error("Zero diagonal element in Gauss-Seidel method at row " + std::to_string(i));
        }
        
        // Calculate: x_i = (b_i - Σ(a_ij * x_j)) / a_ii
        long double sum = 0.0;
        
        // Use NEW values for j < i (already computed in this iteration)
        for (int j = 0; j < i; j++) {
            sum += mat[i][j] * x_current[j];
        }
        
        // Use OLD values for j > i (not yet computed in this iteration)
        for (int j = i + 1; j < rows; j++) {
            sum += mat[i][j] * x_current[j];
        }
        
        x_current[i] = (b_vec[i] - sum) / mat[i][i];
    }
}

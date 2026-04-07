#include "SLE.hpp"
#include "LU.hpp"
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <algorithm>

using namespace std;

// ================= ALGORITHMS =================

void GaussianElimination::basicPivoting(int currIndex) {
    int maxRow = currIndex;
    long double maxVal = fabsl(mat[currIndex][currIndex]);
    for (int i = currIndex + 1; i < rows; i++) {
        if (fabsl(mat[i][currIndex]) > maxVal) {
            maxVal = fabsl(mat[i][currIndex]);
            maxRow = i;
        }
    }
    if (maxVal < 1e-18)
        throw runtime_error("Matrix is singular or pivot is zero.");
    if (maxRow != currIndex) swap(mat[currIndex], mat[maxRow]);
}

void GaussianElimination::upperTriangularWithoutPivot() {
    for (int i = 0; i < rows; i++) {
        if (fabsl(mat[i][i]) < 1e-18)
            throw runtime_error("Zero pivot encountered (no pivoting).");
        long double diag = mat[i][i];
        for (int j = i; j < cols; j++) mat[i][j] /= diag;
        for (int j = i + 1; j < rows; j++) {
            long double factor = mat[j][i];
            for (int k = i; k < cols; k++)
                mat[j][k] -= factor * mat[i][k];
        }
    }
}

void GaussianElimination::upperTriangularWithPivot() {
    for (int i = 0; i < rows; i++) {
        basicPivoting(i);
        if (fabsl(mat[i][i]) < 1e-18)
            throw runtime_error("Matrix is singular.");
        long double diag = mat[i][i];
        for (int j = i; j < cols; j++) mat[i][j] /= diag;
        for (int j = i + 1; j < rows; j++) {
            long double factor = mat[j][i];
            for (int k = i; k < cols; k++)
                mat[j][k] -= factor * mat[i][k];
        }
    }
}


vector<long double> SLE::backSubstitutionToVec() const {
    int n = rows;
    vector<long double> sol(n);
    for (int i = n - 1; i >= 0; i--) {
        long double sum = mat[i][cols - 1]; // Assume single RHS column for basic SLE
        for (int j = i + 1; j < n; j++)
            sum -= mat[i][j] * sol[j];
        if (fabsl(mat[i][i]) < 1e-18)
            throw runtime_error("Division by zero in back substitution.");
        sol[i] = sum / mat[i][i];
    }
    return sol;
}

vector<long double> SLE::solve(SolverType method, LUMethod lu_m) {
    if (method == GAUSSIAN) {
        upperTriangularWithPivot();
        solution_vec = backSubstitutionToVec();
    } else {
        // Extract A and B from augmented matrix
        int n = rows;
        Matrix A(n, n);
        Matrix B(n, 1);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) A(i, j) = mat[i][j];
            B(i, 0) = mat[i][cols-1];
        }
        LU lu_solver(n);
        if (lu_m == DOOLITTLE) lu_solver.doolittle(A);
        else if (lu_m == CROUT) lu_solver.crout(A);
        else if (lu_m == CHOLESKY) lu_solver.cholesky(A);
        
        solution_vec = lu_solver.solve(B);
    }
    return solution_vec;
}

Matrix SLE::solveWithPivot() {
    upperTriangularWithPivot();
    solution_vec = backSubstitutionToVec();
    // Return a dummy matrix or update header to return vector
    Matrix res(rows, 1);
    for(int i=0; i<rows; i++) res(i, 0) = solution_vec[i];
    return res;
}

Matrix SLE::solveWithoutPivot() {
    upperTriangularWithoutPivot();
    solution_vec = backSubstitutionToVec();
    Matrix res(rows, 1);
    for(int i=0; i<rows; i++) res(i, 0) = solution_vec[i];
    return res;
}

void Matrix::saveSolution(const string &filename) const {
    ofstream file(filename);
    if (!file) throw runtime_error("Error creating output file.");
    for (int i = 0; i < rows; i++)
        file << i << " " << mat[i][0] << endl;
    file.close();
}


long double Matrix::determinant() const {
    if (!isSquare()) throw runtime_error("Matrix must be square.");
    int n = rows;
    Matrix temp(*this);
    long double det = 1.0;
    int swaps = 0;
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
            if (fabsl(temp.mat[k][i]) > fabsl(temp.mat[maxRow][i]))
                maxRow = k;
        if (fabsl(temp.mat[maxRow][i]) < 1e-18) return 0;
        if (maxRow != i) {
            swap(temp.mat[i], temp.mat[maxRow]);
            swaps++;
        }
        det *= temp.mat[i][i];
        for (int k = i + 1; k < n; k++) {
            long double factor = temp.mat[k][i] / temp.mat[i][i];
            for (int j = i + 1; j < n; j++)
                temp.mat[k][j] -= factor * temp.mat[i][j];
        }
    }
    if (swaps % 2 != 0) det = -det;
    return det;
}

Matrix Matrix::inverse() const {
    if (!isSquare()) throw runtime_error("Inverse needs square matrix.");
    int n = rows;
    // Use GaussianElimination for augmented matrix operations
    GaussianElimination aug(n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug(i, j) = mat[i][j];
        aug(i, n + i) = 1.0;
    }
    aug.upperTriangularWithPivot();
    Matrix inv(n, n);
    for (int k = 0; k < n; k++) {
        for (int i = n - 1; i >= 0; i--) {
            long double sum = aug(i, n + k);
            for (int j = i + 1; j < n; j++)
                sum -= aug(i, j) * inv(j, k);
            inv(i, k) = sum / aug(i, i);
        }
    }
    return inv;
}

vector<Matrix::GershgorinDisk> Matrix::gershgorinDisks() const {
    if (!isSquare()) throw runtime_error("Gershgorin analysis requires a square matrix.");

    vector<GershgorinDisk> disks(rows);
    for (int i = 0; i < rows; i++) {
        long double radius = 0.0L;
        for (int j = 0; j < cols; j++) {
            if (i != j) radius += fabsl(mat[i][j]);
        }
        disks[i] = {mat[i][i], radius};
    }

    return disks;
}

pair<long double, long double> Matrix::gershgorinRealBounds() const {
    vector<GershgorinDisk> disks = gershgorinDisks();

    long double minBound = disks[0].center - disks[0].radius;
    long double maxBound = disks[0].center + disks[0].radius;

    for (const auto &disk : disks) {
        minBound = min(minBound, disk.center - disk.radius);
        maxBound = max(maxBound, disk.center + disk.radius);
    }

    return {minBound, maxBound};
}

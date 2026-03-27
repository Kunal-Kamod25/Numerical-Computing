#include "LU.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;

/*
    Constructor

    Initializes L and U matrices
    and prepares permutation vector.
*/
LU::LU(int n) : SLE(n, n)
{
    L = Matrix(n,n);
    U = Matrix(n,n);

    P.resize(n);

    for(int i=0;i<n;i++)
        P[i] = i;
}

LU::LU(const Matrix &A) : SLE(A)
{
    int n = A.rows;
    L = Matrix(n,n);
    U = Matrix(n,n);
    P.resize(n);
    for(int i=0;i<n;i++) P[i] = i;
}

LU::LU(const SLE &sle) : SLE(sle)
{
    int n = this->rows;
    L = Matrix(n,n);
    U = Matrix(n,n);
    P.resize(n);
    for(int i=0;i<n;i++) P[i] = i;
}

// DOOLITTLE METHOD (WITH PARTIAL PIVOTING)
void LU::doolittle(const Matrix &A)
{
    int n = A.rows;

    // Reset matrices
    L = Matrix(n,n);
    U = Matrix(n,n);

    Matrix temp = A;   // Copy of A (we modify this)

    // Initialize permutation vector
    for(int i=0;i<n;i++)
        P[i] = i;

    for(int k = 0; k < n; k++)
    {
        /*
            Pivoting step
            Find the row with the largest value
            in the current column.
        */

        long double maxVal = 0;
        int pivotRow = k;

        for(int i = k; i < n; i++)
        {
            if(fabsl(temp.mat[i][k]) > maxVal)
            {
                maxVal = fabsl(temp.mat[i][k]);
                pivotRow = i;
            }
        }

        if(maxVal < 1e-18)
            throw runtime_error("Matrix is singular.");

        // Swap rows if needed
        if(pivotRow != k)
        {
            swap(temp.mat[k], temp.mat[pivotRow]);
            swap(P[k], P[pivotRow]);
            // Also swap already computed elements of L
            for(int s = 0; s < k; s++)
                swap(L.mat[k][s], L.mat[pivotRow][s]);
        }
        // Compute U
        for(int j = k; j < n; j++)
        {
            long double sum = 0;
            for(int s = 0; s < k; s++)
                sum += L.mat[k][s] * U.mat[s][j];

            U.mat[k][j] = temp.mat[k][j] - sum;
        }
        // Compute L
        L.mat[k][k] = 1;

        for(int i = k + 1; i < n; i++)
        {
            long double sum = 0;
            for(int s = 0; s < k; s++)
                sum += L.mat[i][s] * U.mat[s][k];

            L.mat[i][k] = (temp.mat[i][k] - sum) / U.mat[k][k];
        }
    }
}

//CROUT METHOD (WITH PARTIAL PIVOTING)
void LU::crout(const Matrix &A)
{
    int n = A.rows;

    L = Matrix(n,n);
    U = Matrix(n,n);

    Matrix temp = A;
    for(int i=0;i<n;i++)
        P[i] = i;

    for(int j = 0; j < n; j++)
    {
        // Pivot selection
        long double maxVal = 0;
        int pivotRow = j;

        for(int i=j;i<n;i++)
        {
            if(fabsl(temp.mat[i][j]) > maxVal)
            {
                maxVal = fabsl(temp.mat[i][j]);
                pivotRow = i;
            }
        }

        if(maxVal < 1e-18)
            throw runtime_error("Matrix is singular.");

        if(pivotRow != j)
        {
            swap(temp.mat[j], temp.mat[pivotRow]);
            swap(P[j], P[pivotRow]);
            // Also swap already computed elements of L
            for(int k = 0; k < j; k++)
                swap(L.mat[j][k], L.mat[pivotRow][k]);
        }

        // Compute L
        for(int i = j; i < n; i++)
        {
            long double sum = 0;
            for(int k = 0; k < j; k++)
                sum += L.mat[i][k] * U.mat[k][j];

            L.mat[i][j] = temp.mat[i][j] - sum;
        }
        U.mat[j][j] = 1;

        // Compute U
        for(int i = j + 1; i < n; i++)
        {
            long double sum = 0;
            for(int k = 0; k < j; k++)
                sum += L.mat[j][k] * U.mat[k][i];

            U.mat[j][i] = (temp.mat[j][i] - sum) / L.mat[j][j];
        }
    }
}

// CHOLESKY METHOD
void LU::cholesky(const Matrix &A)
{
    int n = A.rows;

    L = Matrix(n,n);
    U = Matrix(n,n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            long double sum = 0;
            for(int k = 0; k < j; k++)
                sum += L.mat[i][k] * L.mat[j][k];

            if(i == j)
            {
                long double value = A.mat[i][i] - sum;
                if(value <= 0)
                    throw runtime_error("Matrix not positive definite.");

                L.mat[i][j] = sqrt(value);
            }
            else
            {
                L.mat[i][j] = (A.mat[i][j] - sum) / L.mat[j][j];
            }
        }
    }
    // U is transpose of L
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            U.mat[i][j] = L.mat[j][i];
}

// SOLVE SYSTEM
vector<long double> LU::solve(const Matrix &B)
{
    int n = L.rows;
    Matrix y(n,1);

    Matrix PB(n,1);

    for(int i=0;i<n;i++)
        PB.mat[i][0] = B.mat[P[i]][0];

    // Forward substitution: Ly = PB
    for(int i = 0; i < n; i++)
    {
        long double sum = PB.mat[i][0];
        for(int j = 0; j < i; j++)
            sum -= L.mat[i][j] * y.mat[j][0];

        y.mat[i][0] = sum / L.mat[i][i];
    }

    solution_vec.resize(n);

    // Back substitution: Ux = y
    for(int i = n-1; i >= 0; i--)
    {
        long double sum = y.mat[i][0];

        for(int j = i+1; j < n; j++)
            sum -= U.mat[i][j] * solution_vec[j];

        solution_vec[i] = sum / U.mat[i][i];
    }
    return solution_vec;
}
#include "Matrix.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// ================= DEFAULT CONSTRUCTOR =================
Matrix::Matrix()
{
    rows = 0;
    cols = 0;
}

// ================= PARAMETERIZED CONSTRUCTOR =================
Matrix::Matrix(int r, int c)
{
    if (r <= 0 || c <= 0)
        throw invalid_argument("Matrix size must be positive.");

    rows = r;
    cols = c;

    mat.resize(rows, vector<long double>(cols, 0));
}

// ================= COPY CONSTRUCTOR =================
Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    mat = other.mat;
}

// ================= OPERATOR + =================
Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for addition.");

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] + other.mat[i][j];

    return result;
}

// ================= OPERATOR - =================
Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for subtraction.");

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] - other.mat[i][j];

    return result;
}

// ================= READ FROM FILE =================
void Matrix::readFromFile(const string &filename)
{
    ifstream file(filename);

    if (!file)
        throw runtime_error("Error opening file.");

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(file >> mat[i][j]))
                throw runtime_error("Error reading matrix data.");

    file.close();
}
// ================= BASIC PIVOTING =================
void Matrix::basicPivoting(int currIndex)
{
    int maxRow = currIndex;
    long double maxRatio = 0.0;

    for (int i = currIndex; i < rows; i++)
    {
        long double rowMax = 0.0;

        // Find largest element in row
        for (int j = currIndex; j < cols; j++)
            rowMax = max(rowMax, fabsl(mat[i][j]));

        if (rowMax == 0.0)
            throw runtime_error("Zero row encountered.");

        long double ratio = fabsl(mat[i][currIndex]) / rowMax;

        if (ratio > maxRatio)
        {
            maxRatio = ratio;
            maxRow = i;
        }
    }

    if (fabsl(mat[maxRow][currIndex]) < 1e-18)
        throw runtime_error("Matrix is singular or nearly singular.");

    if (maxRow != currIndex)
        swap(mat[currIndex], mat[maxRow]);
}

// ================= WITH PIVOT =================
void Matrix::upperTriangularWithPivot()
{
    for (int i = 0; i < rows; i++)
    {
        basicPivoting(i);

        if (abs(mat[i][i]) < 1e-18)
            throw runtime_error("Matrix is singular or nearly singular.");

        long double diag = mat[i][i];

        for (int j = i; j < cols; j++)
            mat[i][j] /= diag;

        for (int j = i + 1; j < rows; j++)
        {
            long double factor = mat[j][i];

            for (int k = i; k < cols; k++)
                mat[j][k] -= factor * mat[i][k];
        }
    }
}

// ================= BACK SUBSTITUTION =================
Matrix Matrix::backSubstitution() const
{
    int n = rows;
    int m = cols - n;

    Matrix sol(n, m);

    for (int k = 0; k < m; k++)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            long double sum = mat[i][n + k];

            for (int j = i + 1; j < n; j++)
                sum -= mat[i][j] * sol.mat[j][k];

            if (abs(mat[i][i]) < 1e-18)
                throw runtime_error("Division by zero in back substitution.");

            sol.mat[i][k] = sum / mat[i][i];
        }
    }

    return sol;
}

Matrix Matrix::solveWithPivot()
{
    upperTriangularWithPivot();
    return backSubstitution();
}

// ================= SAVE SOLUTION (Formatted x,y,z style) =================
void Matrix::saveSolution(const string &filename) const
{
    ofstream file(filename);
    if (!file)
        throw runtime_error("Error creating output file.");

    long double maxVal = 0.0;

    for (int i = 0; i < rows; i++)
        maxVal = max(maxVal, fabsl(mat[i][0]));

    for (int i = 0; i < rows; i++)
        file << i << " " << mat[i][0] / maxVal << endl;

    file.close();
}
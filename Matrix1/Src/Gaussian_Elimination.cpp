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

// ================= DISPLAY =================
void Matrix::display() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << setw(12) << mat[i][j] << " ";
        cout << endl;
    }
}

// ================= BASIC PIVOTING =================
void Matrix::basicPivoting(int currIndex)
{
    int maxRow = currIndex;
    // Look for the LARGEST absolute value to ensure stability
    for (int i = currIndex + 1; i < rows; i++)
    {
        if (std::abs(mat[i][currIndex]) > std::abs(mat[maxRow][currIndex]))
        {
            maxRow = i;
        }
    }

    if (std::abs(mat[maxRow][currIndex]) < 1e-20) // Effectively zero
        throw runtime_error("Matrix is singular. Cannot pivot.");

    if (maxRow != currIndex)
        swap(mat[currIndex], mat[maxRow]);

}

// ================= WITHOUT PIVOT =================
void Matrix::upperTriangularWithoutPivot()
{
    for (int i = 0; i < rows; i++)
    {
        if (mat[i][i] == 0)
            throw runtime_error("Zero pivot encountered.");

        long double diag = mat[i][i];

        for (int j = 0; j < cols; j++)
            mat[i][j] /= diag;

        for (int j = i + 1; j < rows; j++)
        {
            long double factor = mat[j][i];

            for (int k = 0; k < cols; k++)
                mat[j][k] -= factor * mat[i][k];
        }
    }
}

// ================= WITH PIVOT =================
void Matrix::upperTriangularWithPivot()
{
    for (int i = 0; i < rows; i++)
    {
        if (mat[i][i] == 0)
            basicPivoting(i);

        if (mat[i][i] == 0)
            throw runtime_error("Matrix is singular after pivoting.");

        long double diag = mat[i][i];

        for (int j = 0; j < cols; j++)
            mat[i][j] /= diag;

        for (int j = i + 1; j < rows; j++)
        {
            long double factor = mat[j][i];

            for (int k = 0; k < cols; k++)
                mat[j][k] -= factor * mat[i][k];
        }
    }
}

// ================= BACK SUBSTITUTION =================
Matrix Matrix::backSubstitution() const
{
    // rows is 225, cols is 226 (Augmented)
    Matrix sol(rows, 1);

    for (int i = rows - 1; i >= 0; i--)
    {
        // Start with the value in the augmented column (the RHS)
        long double sum = mat[i][cols - 1];

        // Subtract known values. Note: j stops at rows (which is cols-1)
        for (int j = i + 1; j < rows; j++)
        {
            sum -= mat[i][j] * sol.mat[j][0];
        }

        // Divide by the diagonal element
        if (std::abs(mat[i][i]) < 1e-20)
            throw runtime_error("Division by zero in back substitution.");
            
        sol.mat[i][0] = sum / mat[i][i];
    }

    return sol;
}

// ================= SOLVE =================
Matrix Matrix::solveWithoutPivot()
{
    upperTriangularWithoutPivot();
    return backSubstitution();
}

Matrix Matrix::solveWithPivot()
{
    upperTriangularWithPivot();
    return backSubstitution();
}

// ================= SAVE FOR GNUPLOT =================
void Matrix::saveSolution(const string &filename) const
{
    ofstream file(filename);

    if (!file)
        throw runtime_error("Error creating output file.");

    for (int i = 0; i < rows; i++)
        file << i + 1 << " " << mat[i][0] << endl;

    file.close();
}
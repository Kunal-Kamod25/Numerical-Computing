#include "Matrix.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// ================= DEFAULT CONSTRUCTOR =================
Matrix::Matrix()
{
    rows = 0;   // initialize rows to 0
    cols = 0;   // initialize cols to 0
}

// ================= PARAMETERIZED CONSTRUCTOR =================
Matrix::Matrix(int r, int c)
{
    rows = r;   // set number of rows
    cols = c;   // set number of columns

    // allocate matrix with 0 initial values
    mat.resize(rows, vector<long double>(cols, 0));
}

// ================= COPY CONSTRUCTOR =================
Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;   // copy rows
    cols = other.cols;   // copy cols
    mat = other.mat;     // vector automatically deep copies
}

// ================= OPERATOR + =================
Matrix Matrix::operator+(const Matrix &other)
{
    Matrix result(rows, cols);  // create result matrix

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] + other.mat[i][j];  // element-wise addition

    return result;
}

// ================= OPERATOR - =================
Matrix Matrix::operator-(const Matrix &other)
{
    Matrix result(rows, cols);  // create result matrix

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] - other.mat[i][j];  // element-wise subtraction

    return result;
}

// ================= READ FROM FILE =================
void Matrix::readFromFile(string filename)
{
    ifstream file(filename);  // open input file

    if (!file)
    {
        cout << "Error opening file!\n";
        exit(1);
    }

    // read matrix values from file
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            file >> mat[i][j];

    file.close();  // close file
}

// ================= DISPLAY MATRIX =================
void Matrix::display() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << setw(12) << mat[i][j] << " ";
        cout << endl;
    }
}

// ================= CHECK SYMMETRIC =================
bool Matrix::isSymmetric() const
{
    if (rows != cols)  // must be square
        return false;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (mat[i][j] != mat[j][i])
                return false;

    return true;
}

// ================= CHECK DIAGONALLY DOMINANT =================
bool Matrix::isDiagonallyDominant() const
{
    for (int i = 0; i < rows; i++)
    {
        long double sum = 0;

        for (int j = 0; j < cols; j++)
            if (i != j)
                sum += abs(mat[i][j]);

        if (abs(mat[i][i]) < sum)
            return false;
    }

    return true;
}

// ================= MAKE DIAGONALLY DOMINANT =================
bool Matrix::makeDiagonallyDominant()
{
    for (int i = 0; i < rows; i++)
        for (int j = i + 1; j < rows; j++)
            if (abs(mat[j][i]) > abs(mat[i][i]))
                swap(mat[i], mat[j]);

    return isDiagonallyDominant();
}

// ================= BASIC PIVOTING =================
void Matrix::basicPivoting(int currIndex)
{
    for (int i = currIndex + 1; i < rows; i++)
    {
        if (mat[i][currIndex] != 0)
        {
            swap(mat[i], mat[currIndex]);
            return;
        }
    }
}

// ================= WITHOUT PIVOT =================
void Matrix::upperTriangularWithoutPivot()
{
    for (int i = 0; i < rows; i++)
    {
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
Matrix Matrix::backSubstitution()
{
    Matrix sol(rows, 1);

    for (int i = rows - 1; i >= 0; i--)
    {
        sol.mat[i][0] = mat[i][cols - 1];

        for (int j = i + 1; j < rows; j++)
            sol.mat[i][0] -= mat[i][j] * sol.mat[j][0];
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
void Matrix::saveSolution(string filename)
{
    ofstream file(filename);

    for (int i = 0; i < rows; i++)
        file << i + 1 << " " << mat[i][0] << endl;

    file.close();
}
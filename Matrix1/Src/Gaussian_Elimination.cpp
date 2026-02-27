#include "Matrix.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// ================= BASE CLASS IMPLEMENTATION =================

// Default Constructor
BaseMatrix::BaseMatrix()
{
    rows = 0;
    cols = 0;
}

// Parameterized Constructor
BaseMatrix::BaseMatrix(int r, int c)
{
    if (r <= 0 || c <= 0)
        throw invalid_argument("Matrix size must be positive.");

    rows = r;
    cols = c;

    mat.resize(rows, vector<long double>(cols, 0));
}

// -----------------------------------------------------------------------
// COPY CONSTRUCTOR - DEEP COPY EXPLANATION
// -----------------------------------------------------------------------
// In C++, there are two kinds of copies:
//
// SHALLOW COPY:
//   - Just copies the pointer or reference, not the actual data
//   - Both objects point to the SAME memory
//   - If one changes data, the other is affected too — dangerous!
//   - C++ default copy does shallow copy for raw pointers (int*, etc.)
//
// DEEP COPY:
//   - Actually copies all the data into a NEW memory location
//   - Both objects are fully independent
//   - Changing one does NOT affect the other
//
// In OUR program:
//   - We use std::vector<std::vector<long double>> for mat
//   - std::vector already manages its own memory and copies deeply by default
//   - So when we write:  mat = other.mat;
//     it creates a brand new 2D vector with all values copied
//     this IS a deep copy — not just copying a pointer
//
// Example in our code:
//   Matrix temp = Aug;  <-- this calls copy constructor
//   Now temp.mat and Aug.mat are completely separate
//   When temp gets modified by solveWithoutPivot(), Aug stays unchanged
//   This is exactly why we can try both pivot and no-pivot with same Aug
//
// If mat were a raw pointer (long double**), default copy would be shallow
// and modifying temp would corrupt Aug — that would be a bug!
// -----------------------------------------------------------------------
BaseMatrix::BaseMatrix(const BaseMatrix &other)
{
    rows = other.rows;
    cols = other.cols;
    mat = other.mat; // deep copy because std::vector copies all elements
}

// Read From File
void BaseMatrix::readFromFile(const string &filename)
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


// ================= DERIVED CLASS IMPLEMENTATION =================

// Constructors
Matrix::Matrix() : BaseMatrix() {}

Matrix::Matrix(int r, int c) : BaseMatrix(r, c) {}

// copy constructor for Matrix calls base copy constructor
// this ensures mat (the 2D vector) is deep copied as explained above
Matrix::Matrix(const Matrix &other) : BaseMatrix(other) {}


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


// ================= OPERATOR * (MATRIX MULTIPLICATION) =================
// Standard matrix multiplication: result[i][j] = sum of row i of A * col j of B
// A must have same number of cols as B has rows
// We copy *this into a local object to show how copy works here
Matrix Matrix::operator*(const Matrix &other) const
{
    // cols of left matrix must equal rows of right matrix
    if (cols != other.rows)
        throw invalid_argument("Matrix size mismatch for multiplication. Cols of A must equal rows of B.");

    // result size: rows of A x cols of B
    Matrix result(rows, other.cols);

    // we copy *this just to demonstrate copy constructor usage
    // in multiplication we don't actually need to modify *this
    // but this shows deep copy in action — selfCopy is fully independent
    Matrix selfCopy(*this); // calls copy constructor — deep copy of mat

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++)
        {
            long double sum = 0.0;
            for (int k = 0; k < cols; k++)
                sum += selfCopy.mat[i][k] * other.mat[k][j]; // use copied object
            result.mat[i][j] = sum;
        }

    return result;
}


// ================= OPERATOR / (ELEMENT-WISE DIVISION) =================
// Divides each element of this matrix by corresponding element of other
// Both matrices must be same size
// Division by zero is checked for each element
Matrix Matrix::operator/(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for division.");

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            // BUG FIX: must check for zero before dividing
            if (fabsl(other.mat[i][j]) < 1e-18)
                throw runtime_error("Division by zero in operator/.");

            result.mat[i][j] = mat[i][j] / other.mat[i][j];
        }

    return result;
}


// ================= BASIC/PARTIAL PIVOTING =================
// BUG NOTE: original code was fine here
// just making sure cols check uses full augmented width — it does, ok
void Matrix::basicPivoting(int currIndex)
{
    int maxRow = currIndex;
    long double maxRatio = 0.0;

    for (int i = currIndex; i < rows; i++)
    {
        long double rowMax = 0.0;

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

// ================= UPPER TRIANGULAR WITHOUT PIVOT =================
// BUG FIX: original used abs() which for long double may call int version
// should use fabsl() for long double to be safe and consistent
void Matrix::upperTriangularWithoutPivot()
{
    for (int i = 0; i < rows; i++)
    {
        if (fabsl(mat[i][i]) < 1e-18) // BUG FIX: was abs(), now fabsl()
            throw runtime_error("Zero pivot encountered (no pivoting).");

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

// ================= UPPER TRIANGULAR WITH PIVOT =================
// BUG FIX: same abs() -> fabsl() fix here too
void Matrix::upperTriangularWithPivot()
{
    for (int i = 0; i < rows; i++)
    {
        basicPivoting(i);

        if (fabsl(mat[i][i]) < 1e-18) // BUG FIX: was abs(), now fabsl()
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


// ================= BACK SUBSTITUTION - LINE BY LINE EXPLANATION =================
Matrix Matrix::backSubstitution() const
{
    // n = number of equations = number of rows in augmented matrix
    // for a 3x4 augmented matrix (3 equations, 1 rhs), n=3
    int n = rows;

    // m = number of right hand side columns
    // augmented matrix is [A | B], cols = n + m, so m = cols - n
    // example: 3 equations, 2 rhs vectors → cols=5, m=2
    int m = cols - n;

    // create solution matrix: n rows (one per unknown), m cols (one per rhs)
    Matrix sol(n, m);

    // loop over each rhs column separately
    // if we have multiple rhs vectors, solve for each one
    for (int k = 0; k < m; k++)
    {
        // back substitution goes from BOTTOM row to TOP row
        // because bottom row has only 1 unknown, easy to solve
        // then use that to solve row above, and so on
        for (int i = n - 1; i >= 0; i--)
        {
            // start with the rhs value for this row and this rhs column k
            // mat[i][n + k] is the value from the B part of augmented matrix
            long double sum = mat[i][n + k];

            // subtract contributions of already-solved unknowns below row i
            // after upper triangular form, mat[i][j] for j > i are the coefficients
            // sol.mat[j][k] is the already computed solution for unknown j
            for (int j = i + 1; j < n; j++)
                sum -= mat[i][j] * sol.mat[j][k];

            // BUG FIX: was abs(), should be fabsl() for long double
            if (fabsl(mat[i][i]) < 1e-18)
                throw runtime_error("Division by zero in back substitution.");

            // after upper triangular, diagonal should be 1.0 (we divided by diag earlier)
            // but we still divide here for safety in case it wasnt normalized
            // sol[i][k] = (rhs - known terms) / diagonal coefficient
            sol.mat[i][k] = sum / mat[i][i];
        }
    }

    // return the full solution matrix
    // if m=1, it's a column vector of all unknowns x1, x2, ... xn
    return sol;
}


// ================= SOLVE FUNCTION =================
Matrix Matrix::solveWithPivot()
{
    upperTriangularWithPivot();
    return backSubstitution();
}

// ================= SOLVE FUNCTION =================
Matrix Matrix::solveWithoutPivot()
{
    upperTriangularWithoutPivot();
    return backSubstitution();
}

// ================= SAVE SOLUTION =================
void Matrix::saveSolution(const string &filename) const
{
    ofstream file(filename);

    if (!file)
        throw runtime_error("Error creating output file.");

    for (int i = 0; i < rows; i++)
        file << i << " " << mat[i][0] << endl;

    file.close();
}
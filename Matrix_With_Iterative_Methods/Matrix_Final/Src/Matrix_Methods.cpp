#include "Matrix.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// ================= BASE CLASS IMPLEMENTATION =================

BaseMatrix::BaseMatrix() {
    rows = 0;
    cols = 0;
}

BaseMatrix::BaseMatrix(int r, int c) {
    if (r <= 0 || c <= 0)
        throw invalid_argument("Matrix size must be positive.");
    rows = r;
    cols = c;
    mat.resize(rows, vector<long double>(cols, 0));
}

BaseMatrix::BaseMatrix(const BaseMatrix &other) {
    rows = other.rows;
    cols = other.cols;
    mat = other.mat;
}

void BaseMatrix::readFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) throw runtime_error("Error opening file.");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(file >> mat[i][j]))
                throw runtime_error("Error reading matrix data.");
    file.close();
}

void Matrix::readFromFile(const string &filename) {
    BaseMatrix::readFromFile(filename);
}

// ================= DERIVED CLASS IMPLEMENTATION =================

Matrix::Matrix() : BaseMatrix() {}
Matrix::Matrix(int r, int c) : BaseMatrix(r, c) {}
Matrix::Matrix(const Matrix &other) : BaseMatrix(other) {}

// ================= OPERATORS =================

Matrix Matrix::operator+(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for addition.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for subtraction.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (cols != other.rows)
        throw invalid_argument("Matrix size mismatch for multiplication.");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++) {
            long double sum = 0.0;
            for (int k = 0; k < cols; k++)
                sum += mat[i][k] * other.mat[k][j];
            result.mat[i][j] = sum;
        }
    return result;
}

Matrix Matrix::operator/(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Matrix size mismatch for division.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            if (fabsl(other.mat[i][j]) < 1e-18)
                throw runtime_error("Division by zero in operator/.");
            result.mat[i][j] = mat[i][j] / other.mat[i][j];
        }
    return result;
}

long double &Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw out_of_range("Index out of bounds.");
    return mat[i][j];
}

long double Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw out_of_range("Index out of bounds.");
    return mat[i][j];
}

bool Matrix::operator==(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabsl(mat[i][j] - other.mat[i][j]) > 1e-18) return false;
    return true;
}

istream &operator>>(istream &in, Matrix &m) {
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            in >> m.mat[i][j];
    return in;
}

ostream &operator<<(ostream &out, const Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            out << setw(12) << m.mat[i][j] << " ";
        out << endl;
    }
    return out;
}

void Matrix::readFromFile(ifstream &fin) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> mat[i][j];
}

void Matrix::displayToFile(ofstream &fout) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fout << mat[i][j] << " ";
        fout << endl;
    }
}

// ================= UTILITIES =================

bool Matrix::isSquare() const { return rows == cols; }

bool Matrix::isSymmetric() const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < i; j++)
            if (fabsl(mat[i][j] - mat[j][i]) > 1e-18) return false;
    return true;
}

bool Matrix::isIdentity() const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            if (i == j && fabsl(mat[i][j] - 1.0) > 1e-15) return false;
            if (i != j && fabsl(mat[i][j]) > 1e-15) return false;
        }
    return true;
}

bool Matrix::isNull() const {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabsl(mat[i][j]) > 1e-18) return false;
    return true;
}

bool Matrix::isDiagonal() const {
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i != j && fabsl(mat[i][j]) > 1e-18) return false;
    return true;
}

bool Matrix::isDiagonallyDominant() const {
    for (int i = 0; i < rows; i++) {
        long double sum = 0;
        for (int j = 0; j < cols; j++)
            if (i != j) sum += fabsl(mat[i][j]);
        if (fabsl(mat[i][i]) < sum) return false;
    }
    return true;
}

bool Matrix::isTranspose(const Matrix &other) const {
    if (rows != other.cols || cols != other.rows) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fabsl(mat[i][j] - other.mat[j][i]) > 1e-18) return false;
    return true;
}

bool Matrix::makeDiagonallyDominant() {
    int n = rows; // Check the square (n x n) coefficient region
    for (int i = 0; i < n; i++) {
        int bestRow = i;
        long double bestValue = fabsl(mat[i][i]);
        long double rowSum = 0.0;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                rowSum += fabsl(mat[i][j]);
            }
        }

        if (bestValue <= rowSum) {
            // Find a suitable row to swap with
            for (int k = i + 1; k < n; k++) {
                long double potentialDiag = fabsl(mat[k][i]);
                long double potentialSum = 0.0;

                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        potentialSum += fabsl(mat[k][j]);
                    }
                }

                if (potentialDiag > potentialSum) {
                    bestRow = k;
                    break;
                }
            }

            if (bestRow != i) {
                swap(mat[i], mat[bestRow]);
            } else {
                return false; // Cannot make matrix diagonally dominant
            }
        }
    }
    return true;
}

Matrix Matrix::transpose() const {
    Matrix res(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.mat[j][i] = mat[i][j];
    return res;
}

const std::vector<long double>& Matrix::getSolutionVec() const {
    return solution_vec;
}

void Matrix::displayProperties() const {
    cout << "\n--- Matrix Properties ---\n";
    cout << "Symmetric Matrix:           " << (isSymmetric() ? "yes" : "no") << endl;
    cout << "Square Matrix:              " << (isSquare() ? "yes" : "no") << endl;
    cout << "Diagonal Matrix:            " << (isDiagonal() ? "yes" : "no") << endl;
    cout << "Identity Matrix:            " << (isIdentity() ? "yes" : "no") << endl;
    cout << "Null Matrix:                " << (isNull() ? "yes" : "no") << endl;
    cout << "Diagonally Dominant Matrix: " << (isDiagonallyDominant() ? "yes" : "no") << endl;
    cout << "-------------------------\n";
}

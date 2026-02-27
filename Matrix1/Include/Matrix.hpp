#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>

// ================= BASE CLASS =================
class BaseMatrix
{
public:
    int rows, cols;
    std::vector<std::vector<long double>> mat;

    BaseMatrix();
    BaseMatrix(int r, int c);
    BaseMatrix(const BaseMatrix &other);

    void readFromFile(const std::string &filename);
};

// ================= DERIVED CLASS =================
class Matrix : public BaseMatrix
{
public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    // Operator Overloading
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;

    void basicPivoting(int currIndex);
    void upperTriangularWithoutPivot();
    void upperTriangularWithPivot();
    Matrix backSubstitution() const;
    Matrix solveWithPivot();
    Matrix solveWithoutPivot();
    void saveSolution(const std::string &filename) const;
};

#endif
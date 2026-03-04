#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// ================= BASE CLASS =================
class BaseMatrix
{
public:
    int rows, cols;
    std::vector<std::vector<long double>> mat;

    BaseMatrix();
    BaseMatrix(int r, int c);
    BaseMatrix(const BaseMatrix &other);

    // virtual so derived class can override it if needed; Base provides a default
    virtual void readFromFile(const std::string &filename);

    // without this, deleting a derived object through base pointer causes undefined behavior
    virtual ~BaseMatrix() {}
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
    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;

    // Gaussian elimination functions
    void basicPivoting(int currIndex);
    void upperTriangularWithoutPivot();
    void upperTriangularWithPivot();

    // File IO
    void readFromFile(const std::string &filename) override;

    Matrix backSubstitution() const;
    Matrix backsubstitution2() const;

    Matrix solveWithPivot();
    Matrix solveWithoutPivot();

    // Save solution to file
    void saveSolution(const std::string &filename) const;
};

#endif
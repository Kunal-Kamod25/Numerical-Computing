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

    virtual void readFromFile(const std::string &filename);

    virtual ~BaseMatrix() {}
};


// ================= DERIVED CLASS =================
class Matrix : public BaseMatrix
{
public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    // ================= OPERATORS =================
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;

    // File IO
    void readFromFile(const std::string &filename) override;

    // ================= GAUSSIAN ELIMINATION =================
    #include "gauss_elimination.hpp"

    // ================= SOLVE LINEAR EQUATIONS =================
    #include "SLE.hpp"
};

#endif
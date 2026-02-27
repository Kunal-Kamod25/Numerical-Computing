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

    // made virtual so derived class Matrix can override it if needed
    // without virtual, even if Matrix overrides it, base pointer would call base version
    virtual void readFromFile(const std::string &filename);

    // virtual destructor is important when using inheritance
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

    // ---- NEW ----
    // operator* : matrix multiplication (uses a copy of the object internally)
    Matrix operator*(const Matrix &other) const;

    // operator/ : element-wise division by another matrix (must be same size)
    Matrix operator/(const Matrix &other) const;
    // ---- END NEW ----

    void basicPivoting(int currIndex);
    void upperTriangularWithoutPivot();
    void upperTriangularWithPivot();
    Matrix backSubstitution() const;
    Matrix solveWithPivot();
    Matrix solveWithoutPivot();
    void saveSolution(const std::string &filename) const;
};

#endif
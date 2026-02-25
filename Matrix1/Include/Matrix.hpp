#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>

class Matrix
{
public:
    int rows, cols;
    std::vector<std::vector<long double>> mat;

    // Constructors
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    // Operator Overloading
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;

    // File I/O
    void readFromFile(const std::string &filename);
    void display() const;

    // Gaussian Elimination
    void basicPivoting(int currIndex);
    void upperTriangularWithoutPivot();
    void upperTriangularWithPivot();
    Matrix backSubstitution() const;
    Matrix solveWithoutPivot();
    Matrix solveWithPivot();

    // For GNUPlot
    void saveSolution(const std::string &filename) const;
};

#endif
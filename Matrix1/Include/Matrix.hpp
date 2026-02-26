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

    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;

    void readFromFile(const std::string &filename);
    // void display() const;

    void basicPivoting(int currIndex);
    void upperTriangularWithPivot();
    Matrix backSubstitution() const;
    Matrix solveWithPivot();

    // Modified for formatted solution output
    void saveSolution(const std::string &filename) const;
};

#endif
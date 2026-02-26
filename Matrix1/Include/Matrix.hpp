#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>

// define class
class Matrix
{
public: // accessible outside the class
    int rows, cols;
    std::vector<std::vector<long double>> mat;
    
    // SMF initilizes the object
    Matrix(); // Default constructor
    Matrix(int r, int c); // Parameterized constructor
    Matrix(const Matrix &other); // Copy constructor

    // Matrix operator+(const Matrix &other) const;
    // Matrix operator-(const Matrix &other) const;

    void readFromFile(const std::string &filename);
    // void display() const;

    void basicPivoting(int currIndex);
    void upperTriangularWithPivot();
    Matrix backSubstitution() const;
    Matrix solveWithPivot(); // solve function

    // Modified for formatted solution output
    void saveSolution(const std::string &filename) const;
};

#endif
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>

class Matrix
{
public:
    int rows, cols;  // number of rows and columns

    // 2D matrix using vector (automatic memory handling)
    std::vector<std::vector<long double>> mat;

    // Constructors
    Matrix();                                // Default constructor
    Matrix(int r, int c);                    // Parameterized constructor
    Matrix(const Matrix &other);             // Copy Constructor

    // Operator Overloading
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);

    // File I/O
    void readFromFile(std::string filename);
    void display() const;

    // Matrix Properties
    bool isSymmetric() const;
    bool isDiagonallyDominant() const;
    bool makeDiagonallyDominant();

    // Gaussian Elimination
    void basicPivoting(int currIndex);
    void upperTriangularWithoutPivot();
    void upperTriangularWithPivot();
    Matrix backSubstitution();
    Matrix solveWithoutPivot();
    Matrix solveWithPivot();

    // 🔥 Added for GNUPlot
    void saveSolution(std::string filename);
};

#endif
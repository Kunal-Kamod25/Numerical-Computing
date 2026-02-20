#ifndef G_E_MATRIX_HPP
#define G_E_MATRIX_HPP

#include <iostream>
#include <vector> //create dynamic 2D matrix:
#include <stdexcept> //handle runtime  errors

using namespace std;

// base class for abstraction
class MatrixBase {

protected:
    int rows;   // store number of rows
    int cols;   // store number of columns

public:
    // pure virtual function
    virtual void display() const = 0;

    virtual ~MatrixBase() {}
};


// derived class
class Matrix : public MatrixBase {

private:
    vector<vector<double>> data;   // matrix values
    vector<double> solution;       // solution for augumented matrix

public:
    // constructor
    Matrix(int r, int c);

    // read matrix
    void readMatrix(); // take input from user

    // display matrix
    void display() const override; // const-does not change object //override-ensures it override base class functions

    // gaussian elimination
    void gaussianElimination(); // convert matrix to upper tringular form

    // back substitution
    void backSubstitution(); // final value for variables

    // operator overloading
    Matrix operator+(const Matrix& other); // const - we dont modify other matrix
    Matrix operator-(const Matrix& other); // & pass by reference

    // destructor
    ~Matrix(); // when an object is destroyed it is used to release resources 
};

#endif

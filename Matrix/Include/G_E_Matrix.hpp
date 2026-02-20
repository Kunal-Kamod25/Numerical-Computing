#ifndef G_E_MATRIX_HPP
#define G_E_MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

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
    vector<double> solution;       // solution for AX=B

public:
    // constructor
    Matrix(int r, int c);

    // read matrix
    void readMatrix();

    // display matrix
    void display() const override;

    // gaussian elimination
    void gaussianElimination();

    // back substitution
    void backSubstitution();

    // operator overloading
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);

    ~Matrix();
};

#endif

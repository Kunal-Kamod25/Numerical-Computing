#include "../include/G_E_Matrix.hpp"

// constructor
Matrix::Matrix(int r, int c) {

    // using this pointer
    this->rows = r; //this always refers to object that called function.
    this->cols = c;

    // resize matrix
    matrix.resize(rows); //Creates rows number of vectors.
    
    for(int i = 0; i < rows; i++) {
        matrix[i].resize(cols); //Creates cols number of columns in each row.
    }
}

// read matrix
void Matrix::/*fun belongs to class matrix*/readMatrix() { // take input from user

    cout << "Enter matrix elements row wise:\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            cin >> matrix[i][j];   // Stores user input into matrix.
        }
    }
}

// display matrix
void Matrix::/*fun belongs to class matrix*/display() const { // const-this fun does not change matrix values.

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " "; // prints elements by elements
        }
        cout << endl;
    }
}


// operator +
Matrix Matrix::/*fun belongs to class matrix*/operator+(const Matrix& other) { // it will overloads + operator

    // check size
    if(this->rows != other.rows || this->cols != other.cols) {
        throw runtime_error("Matrix size mismatch for addition");
    }
    Matrix result(this->rows, this->cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

// operator -
Matrix Matrix::/*fun belongs to class matrix*/operator-(const Matrix& other) { // it will overloads - operator

    // check size
    if(this->rows != other.rows || this->cols != other.cols) {
        throw runtime_error("Matrix size mismatch for subtraction");
    }
    Matrix result(this->rows, this->cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}


// gaussian elimination (no pivoting)
void Matrix::gaussianElimination() { // it will convert matrix to upper tringular form

    if(cols != rows + 1) {
        throw runtime_error("Matrix must be augmented (n x n+1)");
    }
    for(int k = 0; k < rows - 1; k++) {
        if(matrix[k][k] == 0) {
            throw runtime_error("Division by zero not allowed");
        }

        for(int i = k + 1; i < rows; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for(int j = k; j < cols; j++) {
                matrix[i][j] = matrix[i][j] - factor * matrix[k][j];
            }
        }
    }
    cout << "\nUpper Triangular Matrix:\n";
    this->display();
}


// back substitution
void Matrix::backSubstitution() {

    solutionVector.resize(rows);
    for(int i = rows - 1; i >= 0; i--) {

        double sum = 0;
        for(int j = i + 1; j < rows; j++) {
            sum = sum + matrix[i][j] * solutionVector[j];
        }

        if(matrix[i][i] == 0) {
            throw runtime_error("Division by zero in back substitution");
        }
        solutionVector[i] = (matrix[i][cols - 1] - sum) / matrix[i][i];
    }

    cout << "\nSolution of AX = B:\n";
    for(int i = 0; i < rows; i++) {
        cout << "x" << i + 1 << " = " << solutionVector[i] << endl;
    }
}

// destructor
Matrix::~Matrix() {
    // Destructor runs automatically when object is destroyed.
}

#include "../include/G_E_Matrix.hpp"

// constructor
Matrix::Matrix(int r, int c) {

    // using this pointer
    this->rows = r; //this always refers to object that called function.
    this->cols = c;

    // resize matrix
    data.resize(rows); //Creates rows number of vectors.
    
    for(int i = 0; i < rows; i++) {
        data[i].resize(cols); //Creates cols number of columns in each row.
    }
}


// read matrix
void Matrix::readMatrix() { // take input from user

    cout << "Enter matrix elements row wise:\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            cin >> data[i][j];   // Stores user input into matrix.
        }
    }
}


// display matrix
void Matrix::display() const { // const-this fun does not change matrix values.

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            cout << data[i][j] << " "; // prints elements by elements
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

            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }

    return result;
}


// operator -
Matrix Matrix::operator-(const Matrix& other) { // it will overloads - operator

    // check size
    if(this->rows != other.rows || this->cols != other.cols) {
        throw runtime_error("Matrix size mismatch for subtraction");
    }

    Matrix result(this->rows, this->cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            result.data[i][j] = this->data[i][j] - other.data[i][j];
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

        if(data[k][k] == 0) {
            throw runtime_error("Division by zero at pivot");
        }

        for(int i = k + 1; i < rows; i++) {

            double factor = data[i][k] / data[k][k];

            for(int j = k; j < cols; j++) {

                data[i][j] = data[i][j] - factor * data[k][j];
            }
        }
    }

    cout << "\nUpper Triangular Matrix:\n";
    this->display();
}


// back substitution
void Matrix::backSubstitution() {

    solution.resize(rows);

    for(int i = rows - 1; i >= 0; i--) {

        double sum = 0;

        for(int j = i + 1; j < rows; j++) {
            sum = sum + data[i][j] * solution[j];
        }

        if(data[i][i] == 0) {
            throw runtime_error("Division by zero in back substitution");
        }

        solution[i] = (data[i][cols - 1] - sum) / data[i][i];
    }

    cout << "\nSolution of AX = B:\n";
    for(int i = 0; i < rows; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}


// destructor
Matrix::~Matrix() {
    // nothing to delete becuse vector handles memory
}

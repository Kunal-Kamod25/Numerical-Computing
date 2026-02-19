#include "../Include/G_E_Matrix.hpp"

// constructor
G_E_Matrix::G_E_Matrix(int r, int c) {
    // use this pointer to assign values
    this->rows = r;
    this->cols = c;
    
    // resize the matrix
    data.resize(rows, vector<double>(cols));
}

// read matrix in terminal
void G_E_Matrix::readMatrix() {
    cout << "Enter the elements of the matrix: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> data[i][j];    // get input from user
        }
    }
} 

// display given matrix 
void G_E_Matrix::displayMatrix() const {
    cout << "Matrix: \n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// Guass-Elimination forward without pivoting
void G_E_Matrix::guassElimination() {

    // check if matrix is augmented 
    if(cols != rows + 1) {
        throw runtime_error("Matrix must be augmented ");
    }

    for(int k = 0; k < rows - 1; k ++) {
        
        // if pivot is zero then division error
        if(data[k][k] == 0) {
            throw runtime_error("Pivot element is zero");
        }

        for(int i = k + 1; i < rows; i++) {
            double factor = data[i][k] / data[k][k];
            for(int j = k; j < cols; j++) {
                // subtracting row
                data[i][j] = data[i][j] - factor * data[k][j];
            }
        }
    }

    cout << "After Gaussian Elimination (Upper triangular):\n";
    this->displayMatrix();  // calling using this pointer
}

// back substitution
void G_E_Matrix::backSubstitution() {

    sol.resize(rows);

    for(int i = rows - 1; i >= 0; i--) {

        double sum = 0;
        for(int j = i + 1; j < rows; j++) {
            sum = sum + data[i][j] * sol[j];
        }

        if(data[i][i] == 0) {
            throw runtime_error("Division by zero in back substitution");
        }

        sol[i] = (data[i][cols - 1] - sum) / data[i][i];
    }

    cout << "Solution is:\n";
    for(int i = 0; i < rows; i++) {
        cout << "x" << i + 1 << " = " << sol[i] << endl;
    }
}

// overriding base class function
void G_E_Matrix::performGaussianElimination() {
    guassElimination();
    backSubstitution();
}

// operator overloading
G_E_Matrix G_E_Matrix::operator+(const G_E_Matrix& other) {

    // checking dimension
    if(this->rows != other.rows || this->cols != other.cols) {
        throw runtime_error("Matrix size mismatch for addition");
    }

    G_E_Matrix result(this->rows, this->cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            // using this pointer
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// destructor
G_E_Matrix::~G_E_Matrix() {
    // nothing special to delete because vector handles memory
}

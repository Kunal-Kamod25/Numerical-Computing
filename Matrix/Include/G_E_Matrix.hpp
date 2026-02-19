#ifndef G_E_Matrix_hpp
#define G_E_Matrix_hpp

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// this is a base class or parent class for abstraction
class G_E_Matrix_Base {
protected:
    int rows; // number of rows
    int cols; // number of columns

public:
    // pure virtual function so this class become abstract class
    virtual void performGaussianElimination() = 0; // cannot create object of base class ovrride in base class

    // added so polymorphism works correctly
    virtual void displayMatrix() const = 0; //const → guarantees it does not modify object.

    // virtual destructor
    virtual ~G_E_Matrix_Base() = default;
};

// this is a child class
class G_E_Matrix : public G_E_Matrix_Base {
private:
    vector<vector<double>> data;  // Matrix data
    vector<double> sol;           // Solution vector

public:
    // constructor
    G_E_Matrix(int row, int col);

    // fun to read matrix from user
    void readMatrix();

    // fun to display matrix 'override parent class'
    void displayMatrix() const override;

    // fun to guass elimination 'forward'
    void guassElimination();

    // back substitution
    void backSubstitution();

    // overriding base class function
    void performGaussianElimination() override;

    // operator overloading for matrix addition
    G_E_Matrix operator+(const G_E_Matrix& other);

    // destructor
    ~G_E_Matrix();  // represents "NOT" or negation.
};

#endif

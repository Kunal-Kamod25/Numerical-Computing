#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// ================= BASE CLASS =================
class BaseMatrix
{
protected:
    int rows, cols;
    std::vector<std::vector<long double>> mat;
    std::vector<long double> solution_vec; // Stores the result of solve

    friend class LU;

public:

    BaseMatrix();
    BaseMatrix(int r, int c);
    BaseMatrix(const BaseMatrix &other);

    virtual void readFromFile(const std::string &filename);

    virtual ~BaseMatrix() {}
};


// ================= DERIVED CLASS =================
class Matrix : public BaseMatrix
{
public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    // Friends
    friend class LU;
    friend std::istream &operator>>(std::istream &in, Matrix &m);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

    // ================= OPERATORS =================
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;
    
    // Access operator (like a[i][j])
    long double &operator()(int i, int j);
    long double operator()(int i, int j) const;
    
    // Comparison
    bool operator==(const Matrix &other) const;

    // File IO
    void readFromFile(const std::string &filename) override;
    void readFromFile(std::ifstream &fin);
    void displayToFile(std::ofstream &fout) const;

    // ================= UTILITY METHODS =================
    bool isSquare() const;
    bool isSymmetric() const;
    bool isIdentity() const;
    bool isNull() const;
    bool isDiagonal() const;
    bool isDiagonallyDominant() const;
    bool isTranspose(const Matrix &other) const;

    bool makeDiagonallyDominant();
    Matrix transpose() const;
    long double determinant() const;
    Matrix inverse() const;

    // Save solution
    void saveSolution(const std::string &filename) const;
    const std::vector<long double>& getSolutionVec() const;
    void displayProperties() const;
};

#endif
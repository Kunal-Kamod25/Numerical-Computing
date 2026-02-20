#include "include/G_E_Matrix.hpp"

int main() {

    try {

        int r, c;

        cout << "Enter number of rows: ";
        cin >> r;

        cout << "Enter number of columns (should be rows + 1 for AX=B): ";
        cin >> c;

        // matrix for gaussian
        Matrix m1(r, c);
        cout << "\nEnter augmented matrix for Gaussian (AX=B):\n";
        m1.readMatrix();

        // second matrix for operations
        Matrix m2(r, c);
        cout << "\nEnter second matrix for addition/subtraction:\n";
        m2.readMatrix();

        cout << "\nFirst Matrix:\n";
        m1.display();

        cout << "\nSecond Matrix:\n";
        m2.display();

        // addition
        Matrix addResult = m1 + m2;
        cout << "\nAddition Result:\n";
        addResult.display();

        // subtraction
        Matrix subResult = m1 - m2;
        cout << "\nSubtraction Result:\n";
        subResult.display();

        // polymorphism example
        MatrixBase* ptr = &m1;
        cout << "\nDisplaying first matrix using base class pointer:\n";
        ptr->display();

        // gaussian on first matrix only
        cout << "\nPerforming Gaussian Elimination:\n";
        m1.gaussianElimination();
        m1.backSubstitution();
    }
    catch(const exception& e) {

        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}

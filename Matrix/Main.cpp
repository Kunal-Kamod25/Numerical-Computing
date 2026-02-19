#include "include/G_E_Matrix.hpp"

int main() {

    try {

        int r, c;

        cout << "Enter number of rows: ";
        cin >> r;

        cout << "Enter number of columns: ";
        cin >> c;

        // base class pointer (runtime polymorphism)
        G_E_Matrix_Base* ptr = new G_E_Matrix(r, c);

        // downcasting so we can access derived functions
        G_E_Matrix* mat = dynamic_cast<G_E_Matrix*>(ptr);

        if(mat == nullptr) {
            throw runtime_error("Casting failed");
        }

        mat->readMatrix();

        cout << "Original Matrix:\n";
        ptr->displayMatrix();  // polymorphism working here

        mat->guassElimination();

        mat->backSubstitution();

        delete ptr;  // freeing memory
    }
    catch(const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

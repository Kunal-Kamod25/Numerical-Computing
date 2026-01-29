#include <iostream>
#include "Complex.h"

using namespace std;

int main() {
    cout << "\n This is MyComplex class demo!" << endl;

    // Initializing two complex numbers
    // c1 = 1 + 2i, c2 = 1 + 3i
    myComplex c1(1, 2), c2(1, 3), c3; 

    // 1) Addition
    c3 = c1.add(c2);
    cout << "Addition: " << c3.a << " + " << c3.b << "i" << endl;

    // 2) Subtraction
    myComplex sub = c1.subtract(c2);
    cout << "Subtraction: " << sub.a << " + (" << sub.b << "i)" << endl;

    // 3) Multiplication
    myComplex mult = c1.multiply(c2);
    cout << "Multiplication: " << mult.a << " + " << mult.b << "i" << endl;

    // 4) Division 
    myComplex div = c1.divide(c2);
    cout << "Division (c1/c2): " << div.a << " + " << div.b << "i" << endl;

    // 5) Complex Conjugate
    myComplex conj = c1.complexConjugate();
    cout << "Conjugate of c1: " << conj.a << " + (" << conj.b << "i)" << endl;

    // 6) Norm (Magnitude)
    cout << "Norm of c1: " << c1.norm() << endl;

    return 0;
}
#include "Complex.h"
#include <iostream>
#include <cmath>

using namespace std;

//(1)Default Constructor
myComplex::myComplex() {
    cout << "\n i am a default constructor in myComplex class....\n";
    a = b = c = 0;
}

//(2)Parameterized Constructor
myComplex::myComplex(float x, float y) {
    cout << "\n i am a parameterized constructor in myComplex class....\n";
    a = x;
    b = y;
}

myComplex::myComplex(float x, float y, float z) {
    cout << "\n i am a parameterized constructor with 3 parameters in myComplex class....\n";
    a = x;
    b = y;
    c = z;
}

myComplex myComplex::add(myComplex tmp) {
    //"Function to add two complex numbers"
    myComplex ans;
    ans.a = a + tmp.a;
    ans.b = b + tmp.b;
    return ans;
}

myComplex myComplex::subtract(myComplex tmp) {
    myComplex ans;
    ans.a = a - tmp.a;
    ans.b = b - tmp.b;
    return ans;
}

myComplex myComplex::multiply(myComplex tmp) {
    // Formula: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    myComplex ans;
    ans.a = (a * tmp.a) - (b * tmp.b);
    ans.b = (a * tmp.b) + (b * tmp.a);
    return ans;
}

myComplex myComplex::divide(myComplex tmp) {
    // Formula: Multiply by conjugate of denominator
    float denominator = (tmp.a * tmp.a) + (tmp.b * tmp.b);
    myComplex ans;
    ans.a = ((a * tmp.a) + (b * tmp.b)) / denominator;
    ans.b = ((b * tmp.a) - (a * tmp.b)) / denominator;
    return ans;
}

myComplex myComplex::complexConjugate() {
    // Conjugate of a + bi is a - bi
    return myComplex(a, -b);
}

float myComplex::norm() {
    // Norm (Magnitude) is sqrt(a^2 + b^2)
    return sqrt((a * a) + (b * b));
}
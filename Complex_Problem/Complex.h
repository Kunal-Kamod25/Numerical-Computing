#include <iostream>
using namespace std;

class myComplex {
public:
    //data members
    float a, b, c;

    //Constructors
    //(1)Default Constructor
    myComplex();

    //(2)Parameterized Constructor
    myComplex(float x, float y);
    myComplex(float x, float y, float z);

    //Operations
    myComplex add(myComplex tmp);
    myComplex subtract(myComplex tmp);
    myComplex multiply(myComplex tmp);
    myComplex divide(myComplex tmp);
    myComplex complexConjugate();
    float norm();
};
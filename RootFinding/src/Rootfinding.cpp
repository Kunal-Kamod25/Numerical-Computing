#include <iostream>
#include <iomanip> // Use for set weidth and preceisions 0.0000.... like thid 
#include <cmath> // this is for absolute values |f(mid)| include math functions
#include "../Include/Rootfinding.hpp"
#include "../Include/Utils.hpp"

using namespace std; // this tells compiler cout means std::cout

void bisectionMethod(double a, double b, double tolerance)// fun declaration datatype double for decimal
{
    double mid; // declare variable to store mid value 
    int iteration = 1; // declare integer varia counter that tells how many times loop runs 

    // print only headers in output like a table
    cout << setw(5)  << "Iter"
         << setw(10) << "a"
         << setw(10) << "b"
         << setw(10) << "mid"
         << setw(15) << "|f(mid)|"
         << endl;


    // print root values and mid approximate root value
    while (true)
    {
        mid = (a + b) / 2; // mid point calculation formula

        cout << setw(5) << iteration
                     << setw(10) << a
                     << setw(10) << b
                     << setw(10) << mid
                     << setw(15) << fixed // Fixed decimal format 
                                << setprecision(4) // set precision means 4 digit after decimal . 
                                << abs(function(mid)) // absolute value no -ve value
                     << defaultfloat // reset formating to default
                     << endl;

        if (abs(function(mid)) < tolerance) // |f(mid)| < tolerance // the root is accurate
             break;
        if (function(a) * function(mid) < 0) // If root lies in [a, mid] → move b
            b = mid;
        else
            a = mid; // If root lies in [mid, b] → move a

        iteration++;
    }

    cout << "\nApproximate Root = " << mid << endl;
}

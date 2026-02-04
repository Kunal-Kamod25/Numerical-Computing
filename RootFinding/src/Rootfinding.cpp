#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/RootFinding.hpp"
#include "../include/Utils.hpp"

using namespace std;

void bisectionMethod(double a, double b, double tolerance)
{
    double mid;
    int iteration = 1;

    if (function(a) * function(b) >= 0)
    {
        cout << "Invalid bracketing interval!" << endl;
        return;
    }

    // print only header
    cout << setw(5)  << "Iter"
         << setw(10) << "a"
         << setw(10) << "b"
         << setw(10) << "mid"
         << setw(15) << "|f(mid)|"
         << endl;


    // print root values
    while (true)
    {
        mid = (a + b) / 2;

        cout << setw(5) << iteration
                     << setw(10) << a
                     << setw(10) << b
                     << setw(10) << mid
                     << setw(15) << fixed << setprecision(4) << abs(function(mid))
                     << defaultfloat
                     << endl;

        if (abs(function(mid)) < tolerance)
             break;
        if (function(a) * function(mid) < 0)
            b = mid;
        else
            a = mid;

        iteration++;
    }

    cout << "\nApproximate Root = " << mid << endl;
}

#include <cmath>
#include "../Include/Utils.hpp"

// this is the main function f(x) = 4x^3 - 3x
double function(double x)
{
    return 4*x*x*x - 3*x;
}

// derivative f'(x) = 12x^2 - 3
double derivative(double x)
{
    return 12*x*x - 3;
}

// rearranged form for fixed point (just example form)
double g(double x)
{
    return (4*x*x*x)/3;
}

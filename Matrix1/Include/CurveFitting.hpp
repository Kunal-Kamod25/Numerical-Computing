#ifndef CURVEFITTING_HPP
#define CURVEFITTING_HPP

#include "Matrix.hpp"
// <vector>, <utility>, <string> etc. already included via Matrix.hpp

// =============================================================
// CurveFitting : public Matrix
// Abstract base class.
// Stores data as n x 2 matrix (inherited mat[][]).
// Subclasses must implement fit(), evaluate(), rms().
// =============================================================

class CurveFitting : public Matrix
{
public:
    CurveFitting();
    CurveFitting(const std::vector<long double> &xi,
                 const std::vector<long double> &fi);
    virtual ~CurveFitting() = default;

    // Store (xi, fi) pairs into inherited Matrix storage (n x 2)
    void setData(const std::vector<long double> &xi,
                 const std::vector<long double> &fi);

    std::vector<long double> getXi() const;
    std::vector<long double> getFi() const;
    int pointCount() const;

    // --- Pure Virtual ---
    virtual void        fit()                         = 0; // Solve for a and b
    virtual long double evaluate(long double x) const = 0; // y = ax + b
    virtual long double rms()                   const = 0; // sqrt(Sum(yi - fi)^2 / N)

    // Shared helper: evaluates fitted curve over [xMin, xMax]
    std::vector<std::pair<long double, long double>>
    evaluateRange(long double xMin, long double xMax, int samples) const;
};


// =============================================================
// LeastSquares : public CurveFitting
// Fits a straight line:  y = ax + b
//
// Minimises S = sum( (a*xi + b - fi)^2 )
//
// Normal equations (from dS/da = 0 and dS/db = 0):
//   a * sum(xi^2) + b * sum(xi) = sum(xi * fi)
//   a * sum(xi)   + b * N       = sum(fi)
//
// RMS Error = sqrt( sum((yi - fi)^2) / N )
// =============================================================

class LeastSquares : public CurveFitting
{
private:
    long double a;   // slope
    long double b;   // intercept

public:
    LeastSquares();
    LeastSquares(const std::vector<long double> &xi,
                 const std::vector<long double> &fi);

    void        fit()                         override; // solve normal equations
    long double evaluate(long double x) const override; // y = ax + b
    long double rms()                   const override; // sqrt(S/N)

    long double getSlope()     const { return a; }
    long double getIntercept() const { return b; }

    void printReport() const;
};

#endif

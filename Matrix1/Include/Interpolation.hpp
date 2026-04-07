#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "Matrix.hpp"
#include <utility>
#include <vector>

// Inherits matrix behavior and adds Gershgorin-based eigenvalue utilities.
class Eigenvalues : public Matrix
{
public:
    Eigenvalues();
    Eigenvalues(int r, int c);
    Eigenvalues(const Matrix &base);

    std::vector<GershgorinDisk> getDisks() const;
    std::pair<long double, long double> getRealBounds() const;
};

// Interpolation base class; stores x-y sample points and common checks.
class Interpolation : public Matrix
{
protected:
    std::vector<long double> xData;
    std::vector<long double> yData;

public:
    Interpolation();
    Interpolation(const std::vector<long double> &x, const std::vector<long double> &y);

    void setData(const std::vector<long double> &x, const std::vector<long double> &y);
    int pointCount() const;
    const std::vector<long double> &getX() const;
    const std::vector<long double> &getY() const;
};

// Lagrange is a concrete interpolation solver built on Interpolation.
class Lagrange : public Interpolation
{
public:
    Lagrange();
    Lagrange(const std::vector<long double> &x, const std::vector<long double> &y);

    long double evaluate(long double x) const;
    std::vector<std::pair<long double, long double>> evaluateRange(long double xMin, long double xMax, int samples) const;
};

#endif

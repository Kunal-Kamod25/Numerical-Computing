#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "Matrix.hpp"
#include <utility>
#include <vector>

// Interpolation base class inheriting matrix behavior.
class Interpolation : public Matrix
{
public:
    Interpolation();
    Interpolation(const std::vector<long double> &x, const std::vector<long double> &y);
    virtual ~Interpolation() = default;

    void setData(const std::vector<long double> &x, const std::vector<long double> &y);
    int pointCount() const;
    std::vector<long double> getX() const;
    std::vector<long double> getY() const;

    virtual long double evaluate(long double x) const = 0;
    virtual std::vector<std::pair<long double, long double>> evaluateRange(long double xMin, long double xMax, int samples) const = 0;
};

// Lagrange is a concrete interpolation solver built on Interpolation.
class Lagrange : public Interpolation
{
public:
    Lagrange();
    Lagrange(const std::vector<long double> &x, const std::vector<long double> &y);

    long double evaluate(long double x) const override;
    std::vector<std::pair<long double, long double>> evaluateRange(long double xMin, long double xMax, int samples) const override;
};

#endif

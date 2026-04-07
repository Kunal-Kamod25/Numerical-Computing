#include "Interpolation.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

Eigenvalues::Eigenvalues() : Matrix() {}

Eigenvalues::Eigenvalues(int r, int c) : Matrix(r, c) {}

Eigenvalues::Eigenvalues(const Matrix &base) : Matrix(base) {}

vector<Matrix::GershgorinDisk> Eigenvalues::getDisks() const
{
    return gershgorinDisks();
}

pair<long double, long double> Eigenvalues::getRealBounds() const
{
    return gershgorinRealBounds();
}

Interpolation::Interpolation() : Matrix(1, 1)
{
    mat[0][0] = 0.0L;
}

Interpolation::Interpolation(const vector<long double> &x, const vector<long double> &y) : Matrix(1, 1)
{
    mat[0][0] = 0.0L;
    setData(x, y);
}

void Interpolation::setData(const vector<long double> &x, const vector<long double> &y)
{
    if (x.size() != y.size() || x.empty())
        throw invalid_argument("Interpolation data must be non-empty and x/y sizes must match.");

    // Ensure no duplicate x-values, because Lagrange basis would divide by zero.
    for (size_t i = 0; i < x.size(); ++i)
        for (size_t j = i + 1; j < x.size(); ++j)
            if (fabsl(x[i] - x[j]) < 1e-18L)
                throw invalid_argument("Interpolation x-values must be unique.");

    xData = x;
    yData = y;
}

int Interpolation::pointCount() const
{
    return static_cast<int>(xData.size());
}

const vector<long double> &Interpolation::getX() const
{
    return xData;
}

const vector<long double> &Interpolation::getY() const
{
    return yData;
}

Lagrange::Lagrange() : Interpolation() {}

Lagrange::Lagrange(const vector<long double> &x, const vector<long double> &y) : Interpolation(x, y) {}

long double Lagrange::evaluate(long double x) const
{
    if (xData.empty())
        throw runtime_error("No interpolation data is set.");

    long double result = 0.0L;

    for (size_t i = 0; i < xData.size(); ++i)
    {
        long double basis = 1.0L;

        for (size_t j = 0; j < xData.size(); ++j)
        {
            if (i == j)
                continue;

            const long double den = xData[i] - xData[j];
            if (fabsl(den) < 1e-18L)
                throw runtime_error("Duplicate x-values found during evaluation.");

            basis *= (x - xData[j]) / den;
        }

        result += yData[i] * basis;
    }

    return result;
}

vector<pair<long double, long double>> Lagrange::evaluateRange(long double xMin, long double xMax, int samples) const
{
    if (samples < 2)
        throw invalid_argument("samples must be >= 2");

    vector<pair<long double, long double>> curve;
    curve.reserve(static_cast<size_t>(samples));

    const long double step = (xMax - xMin) / static_cast<long double>(samples - 1);
    for (int i = 0; i < samples; ++i)
    {
        const long double x = xMin + static_cast<long double>(i) * step;
        curve.push_back({x, evaluate(x)});
    }

    return curve;
}

#include "Interpolation.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;

Interpolation::Interpolation() {}

Interpolation::Interpolation(const vector<long double> &x, const vector<long double> &y)
{
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

    // Store interpolation points directly in inherited Matrix storage as n x 2.
    rows = static_cast<int>(x.size());
    cols = 2;
    mat.assign(static_cast<size_t>(rows), vector<long double>(static_cast<size_t>(cols), 0.0L));
    for (int i = 0; i < rows; ++i)
    {
        mat[static_cast<size_t>(i)][0] = x[static_cast<size_t>(i)];
        mat[static_cast<size_t>(i)][1] = y[static_cast<size_t>(i)];
    }
}

int Interpolation::pointCount() const
{
    return rows;
}

vector<long double> Interpolation::getX() const
{
    vector<long double> x;
    x.reserve(static_cast<size_t>(rows));
    for (int i = 0; i < rows; ++i)
        x.push_back(mat[static_cast<size_t>(i)][0]);
    return x;
}

vector<long double> Interpolation::getY() const
{
    vector<long double> y;
    y.reserve(static_cast<size_t>(rows));
    for (int i = 0; i < rows; ++i)
        y.push_back(mat[static_cast<size_t>(i)][1]);
    return y;
}

Lagrange::Lagrange() : Interpolation() {}

Lagrange::Lagrange(const vector<long double> &x, const vector<long double> &y) : Interpolation(x, y) {}

long double Lagrange::evaluate(long double x) const
{
    if (rows <= 0 || cols < 2 || mat.empty())
        throw runtime_error("No interpolation data is set.");

    long double result = 0.0L;

    for (int i = 0; i < rows; ++i)
    {
        long double basis = 1.0L;

        for (int j = 0; j < rows; ++j)
        {
            if (i == j)
                continue;

            const long double den = mat[static_cast<size_t>(i)][0] - mat[static_cast<size_t>(j)][0];
            if (fabsl(den) < 1e-18L)
                throw runtime_error("Duplicate x-values found during evaluation.");

            basis *= (x - mat[static_cast<size_t>(j)][0]) / den;
        }

        result += mat[static_cast<size_t>(i)][1] * basis;
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

#include "CurveFitting.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;


// ================================================================
//  CurveFitting — abstract base class
// ================================================================

CurveFitting::CurveFitting() : Matrix() {}

CurveFitting::CurveFitting(const vector<long double> &xi,
                           const vector<long double> &fi)
    : Matrix()
{
    setData(xi, fi);
}

// ---------------------------------------------------------------
// setData — stores (xi, fi) into inherited Matrix as n x 2.
//   mat[i][0] = xi
//   mat[i][1] = fi   (fi = given data values)
// Same pattern as Interpolation::setData.
// ---------------------------------------------------------------
void CurveFitting::setData(const vector<long double> &xi,
                           const vector<long double> &fi)
{
    if (xi.empty() || xi.size() != fi.size())
        throw invalid_argument("CurveFitting: xi and fi must be non-empty and same size.");

    rows = static_cast<int>(xi.size());
    cols = 2;
    mat.assign(static_cast<size_t>(rows),
               vector<long double>(static_cast<size_t>(cols), 0.0L));

    for (int i = 0; i < rows; ++i)
    {
        mat[static_cast<size_t>(i)][0] = xi[static_cast<size_t>(i)]; // xi
        mat[static_cast<size_t>(i)][1] = fi[static_cast<size_t>(i)]; // fi
    }
}

int CurveFitting::pointCount() const { return rows; }

vector<long double> CurveFitting::getXi() const
{
    vector<long double> xi;
    xi.reserve(static_cast<size_t>(rows));
    for (int i = 0; i < rows; ++i)
        xi.push_back(mat[static_cast<size_t>(i)][0]);
    return xi;
}

vector<long double> CurveFitting::getFi() const
{
    vector<long double> fi;
    fi.reserve(static_cast<size_t>(rows));
    for (int i = 0; i < rows; ++i)
        fi.push_back(mat[static_cast<size_t>(i)][1]);
    return fi;
}

// Shared evaluateRange — calls the subclass evaluate() via virtual dispatch
vector<pair<long double, long double>>
CurveFitting::evaluateRange(long double xMin, long double xMax, int samples) const
{
    if (samples < 2)
        throw invalid_argument("CurveFitting: samples must be >= 2.");

    vector<pair<long double, long double>> curve;
    curve.reserve(static_cast<size_t>(samples));

    const long double step = (xMax - xMin) / static_cast<long double>(samples - 1);
    for (int i = 0; i < samples; ++i)
    {
        long double x = xMin + static_cast<long double>(i) * step;
        curve.push_back({x, evaluate(x)});
    }
    return curve;
}


// ================================================================
//  LeastSquares — concrete class
//  Linear fit: y = ax + b
//
//  From notes:
//    Minimize S = sum( (a*xi + b - fi)^2 )
//
//    dS/da = 0  =>  a*sum(xi^2) + b*sum(xi) = sum(xi*fi)
//    dS/db = 0  =>  a*sum(xi)   + b*N        = sum(fi)
//
//  Solve the 2x2 system directly (Cramer's rule):
//    det = N * sum(xi^2) - (sum(xi))^2
//    a   = ( N*sum(xi*fi) - sum(xi)*sum(fi) ) / det
//    b   = ( sum(fi)*sum(xi^2) - sum(xi)*sum(xi*fi) ) / det
// ================================================================

LeastSquares::LeastSquares() : CurveFitting(), a(0.0L), b(0.0L) {}

LeastSquares::LeastSquares(const vector<long double> &xi,
                           const vector<long double> &fi)
    : CurveFitting(xi, fi), a(0.0L), b(0.0L)
{}

// ---------------------------------------------------------------
// fit() — Normal Equations (exactly as derived in class notes)
// ---------------------------------------------------------------
void LeastSquares::fit()
{
    if (rows < 2)
        throw runtime_error("LeastSquares: need at least 2 data points.");

    const long double N = static_cast<long double>(rows);

    // Compute summations used in normal equations
    long double sum_xi    = 0.0L;  // sum(xi)
    long double sum_fi    = 0.0L;  // sum(fi)
    long double sum_xi2   = 0.0L;  // sum(xi^2)
    long double sum_xi_fi = 0.0L;  // sum(xi * fi)

    for (int i = 0; i < rows; ++i)
    {
        long double xi = mat[static_cast<size_t>(i)][0];
        long double fi = mat[static_cast<size_t>(i)][1];
        sum_xi    += xi;
        sum_fi    += fi;
        sum_xi2   += xi * xi;
        sum_xi_fi += xi * fi;
    }

    // Determinant of the 2x2 coefficient matrix
    long double det = N * sum_xi2 - sum_xi * sum_xi;

    if (fabsl(det) < 1e-15L)
        throw runtime_error("LeastSquares: singular system — cannot solve normal equations.");

    // Cramer's rule
    a = (N * sum_xi_fi  - sum_xi * sum_fi)  / det;
    b = (sum_fi * sum_xi2 - sum_xi * sum_xi_fi) / det;
}

// ---------------------------------------------------------------
// evaluate(x) — y = ax + b
// ---------------------------------------------------------------
long double LeastSquares::evaluate(long double x) const
{
    return a * x + b;
}

// ---------------------------------------------------------------
// rms() — Root Mean Square error
//   RMS = sqrt( sum( (yi - fi)^2 ) / N )
//   where yi = a*xi + b  is the fitted value
//         fi = actual data point
// ---------------------------------------------------------------
long double LeastSquares::rms() const
{
    long double sumSq = 0.0L;
    for (int i = 0; i < rows; ++i)
    {
        long double xi   = mat[static_cast<size_t>(i)][0];
        long double fi   = mat[static_cast<size_t>(i)][1];
        long double yi   = evaluate(xi);          // predicted
        long double diff = yi - fi;               // residual
        sumSq += diff * diff;
    }
    return sqrtl(sumSq / static_cast<long double>(rows));
}

// ---------------------------------------------------------------
// printReport
// ---------------------------------------------------------------
void LeastSquares::printReport() const
{
    cout << fixed << setprecision(6);
    cout << "\n--- Least Squares Fit Report ---\n";
    cout << "  Data points  N : " << rows << "\n";
    cout << "  Fitted line  : y = " << a << " * x + " << b << "\n";
    cout << "  Slope      a : " << a << "\n";
    cout << "  Intercept  b : " << b << "\n";
    cout << "  RMS Error    : " << rms() << "\n";
    cout << "--------------------------------\n";
}

#include "Interpolation.hpp"
#include "Eigenvalues.hpp"
#include "Gershgorin.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

static bool loadCheckData(const string &fileName, vector<long double> &x, vector<long double> &y)
{
    ifstream in(fileName);
    if (!in)
        return false;

    long double xi, yi;
    while (in >> xi >> yi)
    {
        x.push_back(xi);
        y.push_back(yi);
    }

    return !x.empty();
}

static void saveDataFile(const string &fileName, const vector<long double> &x, const vector<long double> &y)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    for (size_t i = 0; i < x.size(); ++i)
        out << x[i] << " " << y[i] << "\n";
}

static void saveCurveFile(const string &fileName, const vector<pair<long double, long double>> &curve)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    for (const auto &p : curve)
        out << p.first << " " << p.second << "\n";
}

int main()
{
    try
    {
        cout << "\n=== Eigenvalues -> Interpolation -> Lagrange Demo ===\n";

        int n;
        cout << "Enter matrix size (4, 49, or 225): ";
        cin >> n;

        string left;
        if (n == 225)
            left = "Large_Matrix/225left.txt";
        else if (n == 49)
            left = "Large_Matrix/49l.txt";
        else if (n == 4)
            left = "Large_Matrix/Sl.txt";
        else
        {
            cout << "Enter matrix file path: ";
            cin >> left;
        }

        // 1) Gershgorin class inherits from Eigenvalues and computes bounds.
        Gershgorin gersh(n, n);
        gersh.readFromFile(left);

        vector<Matrix::GershgorinDisk> disks = gersh.disks();
        pair<long double, long double> bounds = gersh.realBounds();

        cout << "Gershgorin real interval: [" << bounds.first << ", " << bounds.second << "]\n";

        vector<long double> xData;
        vector<long double> yData;

        // 2) Use matrix-derived data first (index -> disk radius).
        // This keeps x-values unique even when centers repeat.
        const int usable = min(static_cast<int>(disks.size()), 8);
        for (int i = 0; i < usable; ++i)
        {
            xData.push_back(static_cast<long double>(i));
            yData.push_back(disks[i].radius);
        }

        // 3) For the n=49 case (or any unstable input), load known check data.
        // This gives a reliable learning/demo path when matrix-driven interpolation is noisy.
        vector<long double> checkX;
        vector<long double> checkY;
        const bool hasCheck = loadCheckData("Large_Matrix/interpolation_check_data.txt", checkX, checkY);

        if (n == 49 || !hasCheck)
        {
            // Built-in fallback if file is missing; simple smooth polynomial data.
            if (!hasCheck)
            {
                checkX = {-3.0L, -2.0L, -1.0L, 0.0L, 1.0L, 2.0L, 3.0L};
                checkY = {4.0L, 1.0L, 0.0L, 1.0L, 4.0L, 9.0L, 16.0L};
            }
            xData = checkX;
            yData = checkY;
            cout << "Using check dataset for interpolation (stable path for learning).\n";
        }
        else
        {
            cout << "Using matrix-derived dataset for interpolation.\n";
        }

        // 4) Interpolation and Lagrange classes (inheritance chain) in action.
        Lagrange lag(xData, yData);

        const long double xMid = (xData.front() + xData.back()) / 2.0L;
        const long double yMid = lag.evaluate(xMid);

        vector<pair<long double, long double>> curve = lag.evaluateRange(xData.front(), xData.back(), 150);

        saveDataFile("interpolation_points.dat", xData, yData);
        saveCurveFile("lagrange_curve.dat", curve);
        if (!checkX.empty() && !checkY.empty())
            saveDataFile("interpolation_check_points.dat", checkX, checkY);

        ofstream report("interpolation_report.txt");
        if (!report)
            throw runtime_error("Error creating interpolation_report.txt");

        report << fixed << setprecision(10);
        report << "Matrix file: " << left << "\n";
        report << "Gershgorin real interval: " << bounds.first << " " << bounds.second << "\n";
        report << "Interpolation points: " << lag.pointCount() << "\n";
        report << "Evaluation at x_mid=" << xMid << ": " << yMid << "\n";
        report << "Output data files:\n";
        report << "  interpolation_points.dat\n";
        report << "  interpolation_check_points.dat\n";
        report << "  lagrange_curve.dat\n";

        cout << "Saved: interpolation_points.dat, lagrange_curve.dat, interpolation_report.txt\n";
        cout << "Tip: plot both files to compare points vs interpolated curve.\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

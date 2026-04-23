#include "Interpolation.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ============================================================================
// SECTION 1: DATA LOADING & FILE OPERATIONS
// ============================================================================

// Load interpolation points from file (x, y pairs, one per line).
static bool loadInterpolationFile(const string &fileName, 
                                  vector<long double> &x, 
                                  vector<long double> &y)
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

// Save x, y data points to a file.
static void saveDataPoints(const string &fileName, 
                          const vector<long double> &x, 
                          const vector<long double> &y)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    for (size_t i = 0; i < x.size(); ++i)
        out << x[i] << " " << y[i] << "\n";

    out.close();
}

// Save interpolated curve (x, y pairs) to a file.
static void saveInterpolatedCurve(const string &fileName, 
                                 const vector<pair<long double, long double>> &curve)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    for (const auto &p : curve)
        out << p.first << " " << p.second << "\n";

    out.close();
}

// Save summary report of interpolation results.
static void saveReport(const string &fileName,
                      const string &dataSource,
                      int pointCount,
                      long double midX,
                      long double midY)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    out << "=== Lagrange Interpolation Report ===\n";
    out << "Data source: " << dataSource << "\n";
    out << "Number of points: " << pointCount << "\n";
    out << "X range: [" << midX << "]\n";
    out << "Evaluation at midpoint: " << midY << "\n";
    out << "\nOutput files generated:\n";
    out << "  - interpolation_points.dat (original data points)\n";
    out << "  - lagrange_curve.dat (smooth interpolated curve)\n";

    out.close();
}

// ============================================================================
// SECTION 2: MENU & FILE SELECTION
// ============================================================================

// Display test interpolation file choices.
static void displayTestFileMenu()
{
    cout << "\n=== Select Interpolation Test Data ===\n";
    cout << "1. Quadratic (y = x²)\n";
    cout << "2. Exponential (y = e^x)\n";
    cout << "3. Sine (y = sin(x))\n";
    cout << "=========================================\n";
}

// Get user menu choice.
static int getUserChoice(int minVal, int maxVal)
{
    int choice;
    cout << "Enter choice (" << minVal << "-" << maxVal << "): ";
    cin >> choice;
    return choice;
}

// Return interpolation file path based on user choice.
static string selectInterpolationFile(int choice)
{
    switch (choice)
    {
    case 1:
        cout << "Selected: Quadratic (y = x²)\n";
        return "Large_Matrix/interp_quadratic.txt";
    case 2:
        cout << "Selected: Exponential (y = e^x)\n";
        return "Large_Matrix/interp_exponential.txt";
    case 3:
        cout << "Selected: Sine (y = sin(x))\n";
        return "Large_Matrix/interp_sine.txt";
    default:
        cout << "Invalid choice! Using Quadratic.\n";
        return "Large_Matrix/interp_quadratic.txt";
    }
}

// ============================================================================
// SECTION 3: LAGRANGE INTERPOLATION WORKFLOW
// ============================================================================

// Run complete Lagrange interpolation pipeline.
static void runLagrangeInterpolation(const string &dataFile)
{
    // Load data from file.
    vector<long double> xData;
    vector<long double> yData;

    if (!loadInterpolationFile(dataFile, xData, yData))
        throw runtime_error("Failed to load interpolation file: " + dataFile);

    cout << "Loaded " << xData.size() << " data points.\n";

    // Create Lagrange interpolator.
    Lagrange lag(xData, yData);

    // Evaluate at midpoint for testing.
    const long double xMid = (xData.front() + xData.back()) / 2.0L;
    const long double yMid = lag.evaluate(xMid);

    cout << "Evaluation at x_mid=" << xMid << " -> y=" << yMid << "\n";

    // Generate smooth curve by sampling many points.
    const vector<pair<long double, long double>> curve = 
        lag.evaluateRange(xData.front(), xData.back(), 200);

    cout << "Generated " << curve.size() << " interpolation curve points.\n";

    // Save results to files.
    saveDataPoints("interpolation_points.dat", xData, yData);
    saveInterpolatedCurve("lagrange_curve.dat", curve);
    saveReport("interpolation_report.txt", dataFile, lag.pointCount(), xMid, yMid);

    cout << "\n*** Output Files Created ***\n";
    cout << "1. interpolation_points.dat   (original data points)\n";
    cout << "2. lagrange_curve.dat         (smooth interpolated values)\n";
    cout << "3. interpolation_report.txt   (summary report)\n";
    cout << "\nTo visualize: gnuplot> plot 'interpolation_points.dat' with points, 'lagrange_curve.dat'\n";
}

// ============================================================================
// SECTION 4: MAIN PROGRAM ENTRY
// ============================================================================

int main()
{
    try
    {
        cout << "\n╔════════════════════════════════════════════╗\n";
        cout << "║  Lagrange Polynomial Interpolation Demo   ║\n";
        cout << "╚════════════════════════════════════════════╝\n";

        // Display menu and get user choice.
        displayTestFileMenu();
        int choice = getUserChoice(1, 3);
        string dataFile = selectInterpolationFile(choice);

        cout << "\nStarting Lagrange interpolation...\n";

        // Run interpolation pipeline.
        runLagrangeInterpolation(dataFile);

        cout << "\n✓ Interpolation complete!\n";
    }
    catch (const exception &e)
    {
        cerr << "\n✗ Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

#include "Interpolation.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

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

static bool isInterpolationInputCandidate(const fs::path &path)
{
    if (!path.has_extension() || path.extension() != ".txt")
        return false;

    string name = path.filename().string();
    transform(name.begin(), name.end(), name.begin(), [](unsigned char ch)
              { return static_cast<char>(tolower(ch)); });

    return name.find("interp") != string::npos ||
           name.find("lagrange") != string::npos ||
           name.find("check") != string::npos;
}

static vector<fs::path> discoverInterpolationInputFiles()
{
    vector<fs::path> files;

    const vector<fs::path> roots = {fs::path("."), fs::path("Large_Matrix")};
    for (const auto &root : roots)
    {
        if (!fs::exists(root) || !fs::is_directory(root))
            continue;

        for (const auto &entry : fs::directory_iterator(root))
        {
            if (!entry.is_regular_file())
                continue;

            const fs::path p = entry.path();
            if (isInterpolationInputCandidate(p))
                files.push_back(p);
        }
    }

    sort(files.begin(), files.end());
    files.erase(unique(files.begin(), files.end()), files.end());
    return files;
}

static string chooseInterpolationInputFile()
{
    const vector<fs::path> files = discoverInterpolationInputFiles();

    if (!files.empty())
    {
        cout << "\nAvailable interpolation input files:\n";
        for (size_t i = 0; i < files.size(); ++i)
            cout << "  " << (i + 1) << ". " << files[i].generic_string() << "\n";

        cout << "Select file number (1-" << files.size() << ") or 0 for custom path: ";
        int choice = -1;
        if (cin >> choice && choice >= 1 && choice <= static_cast<int>(files.size()))
            return files[static_cast<size_t>(choice - 1)].generic_string();

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string dataFile;
    cout << "Enter interpolation data file path (x y pairs): ";
    cin >> dataFile;
    return dataFile;
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
                      long double evalX,
                      long double evalY)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    out << "=== Lagrange Interpolation Report ===\n";
    out << "Data source: " << dataSource << "\n";
    out << "Number of points: " << pointCount << "\n";
    out << "Evaluation at x=" << evalX << ": " << evalY << "\n";
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
    cout << "4. Discover / Select available data file\n";
    cout << "5. Custom file path\n";
    cout << "=========================================\n";
}

// Get user menu choice.
static int getUserChoice(int minVal, int maxVal)
{
    int choice;
    cout << "Enter choice (" << minVal << "-" << maxVal << "): ";
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return minVal;
    }
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
    case 4:
        return chooseInterpolationInputFile();
    case 5:
    {
        string path;
        cout << "Enter custom file path: ";
        cin >> path;
        return path;
    }
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

    if (xData.size() < 2)
        throw runtime_error("Interpolation file must contain at least 2 points.");

    cout << "Loaded " << xData.size() << " data points.\n";

    // Create Lagrange interpolator.
    Lagrange lag(xData, yData);

    // Evaluate at midpoint or custom x.
    const long double xMid = (xData.front() + xData.back()) / 2.0L;
    long double evalX = xMid;
    
    cout << "Enter custom x to evaluate (or enter " << xMid << " for midpoint): ";
    if (cin >> evalX)
    {
        // Accepted user input
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        evalX = xMid;
    }

    const long double evalY = lag.evaluate(evalX);
    cout << "Evaluation at x=" << evalX << " -> y=" << evalY << "\n";

    // Generate smooth curve by sampling points across data range.
    const vector<pair<long double, long double>> curve = 
        lag.evaluateRange(xData.front(), xData.back(), 200);

    cout << "Generated " << curve.size() << " interpolation curve points.\n";

    // Save results to files.
    saveDataPoints("interpolation_points.dat", xData, yData);
    saveInterpolatedCurve("lagrange_curve.dat", curve);
    saveReport("interpolation_report.txt", dataFile, lag.pointCount(), evalX, evalY);

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
        int choice = getUserChoice(1, 5);
        string dataFile = selectInterpolationFile(choice);

        cout << "\nStarting Lagrange interpolation on: " << dataFile << "\n";

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

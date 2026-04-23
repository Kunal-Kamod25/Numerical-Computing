#include "CurveFitting.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// ---------------------------------------------------------------
// Load (xi, fi) pairs from a file — one pair per line
// ---------------------------------------------------------------
static bool loadData(const string &fileName,
                     vector<long double> &xi,
                     vector<long double> &fi)
{
    ifstream in(fileName);
    if (!in) return false;

    string line;
    while (getline(in, line))
    {
        // skip blank lines and comment lines
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        long double xi_local, fi_local;
        if (iss >> xi_local >> fi_local)
        {
            xi.push_back(xi_local);
            fi.push_back(fi_local);
        }
    }
    return !xi.empty();
}

// ---------------------------------------------------------------
// Save original (xi, fi) points as .dat for gnuplot
// ---------------------------------------------------------------
static void savePoints(const string &file,
                       const vector<long double> &x,
                       const vector<long double> &y)
{
    ofstream out(file);
    if (!out) throw runtime_error("Cannot write: " + file);
    out << fixed << setprecision(10);
    for (size_t i = 0; i < x.size(); ++i)
        out << x[i] << " " << y[i] << "\n";
}

// ---------------------------------------------------------------
// Save fitted curve samples as .dat for gnuplot
// ---------------------------------------------------------------
static void saveCurve(const string &file,
                      const vector<pair<long double, long double>> &curve)
{
    ofstream out(file);
    if (!out) throw runtime_error("Cannot write: " + file);
    out << fixed << setprecision(10);
    for (const auto &p : curve)
        out << p.first << " " << p.second << "\n";
}

// ---------------------------------------------------------------
// Auto-discover .txt data files (same pattern as Interpolation)
// ---------------------------------------------------------------
static vector<fs::path> discoverFiles()
{
    vector<fs::path> files;
    for (const auto &root : {fs::path("."), fs::path("Large_Matrix")})
    {
        if (!fs::exists(root) || !fs::is_directory(root)) continue;
        for (const auto &entry : fs::directory_iterator(root))
        {
            if (!entry.is_regular_file()) continue;
            const fs::path p = entry.path();
            if (!p.has_extension() || p.extension() != ".txt") continue;
            string name = p.filename().string();
            transform(name.begin(), name.end(), name.begin(),
                      [](unsigned char c){ return static_cast<char>(tolower(c)); });
            if (name.find("curve") != string::npos ||
                name.find("fit")   != string::npos ||
                name.find("data")  != string::npos ||
                name.find("notes") != string::npos ||
                name.find("lsq")   != string::npos)
                files.push_back(p);
        }
    }
    sort(files.begin(), files.end());
    return files;
}

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main()
{
    try
    {
        cout << "\n=== Curve Fitting — Least Squares (y = ax + b) ===\n";

        // -- Step 1: pick data file --
        const vector<fs::path> files = discoverFiles();
        string dataFile;

        if (!files.empty())
        {
            cout << "\nAvailable data files:\n";
            for (size_t i = 0; i < files.size(); ++i)
                cout << "  " << (i + 1) << ". " << files[i].generic_string() << "\n";

            cout << "Select (1-" << files.size() << ") or 0 to type path: ";
            int choice = 0;
            if (cin >> choice && choice >= 1 && choice <= static_cast<int>(files.size()))
                dataFile = files[static_cast<size_t>(choice - 1)].generic_string();
            else { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
        }

        if (dataFile.empty())
        {
            cout << "Enter data file path (xi fi pairs, one per line): ";
            cin >> dataFile;
        }

        // -- Step 2: load data --
        vector<long double> xiData, fiData;
        if (!loadData(dataFile, xiData, fiData))
            throw runtime_error("Failed to read data from: " + dataFile);

        cout << "Loaded " << xiData.size() << " points.\n";

        // -- Step 3: fit using LeastSquares (inherits CurveFitting → Matrix) --
        LeastSquares ls(xiData, fiData);
        ls.fit();

        // -- Step 4: print report (a, b, RMS) --
        ls.printReport();

        // -- Step 5: evaluate at a custom x --
        long double xEval;
        cout << "\nEnter x to evaluate on fitted line: ";
        cin >> xEval;
        cout << "  y(" << fixed << setprecision(6) << xEval
             << ") = " << ls.evaluate(xEval) << "\n";

        // -- Step 6: save .dat files --
        savePoints("curvefitting_points.dat", ls.getXi(), ls.getFi());
        const auto curve = ls.evaluateRange(xiData.front(), xiData.back(), 200);
        saveCurve("curvefitting_curve.dat", curve);

        cout << "\nSaved:\n"
             << "  curvefitting_points.dat  (original data points)\n"
             << "  curvefitting_curve.dat   (fitted line, 200 samples)\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

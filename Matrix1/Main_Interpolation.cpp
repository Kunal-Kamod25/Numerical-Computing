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
        cout << "Available interpolation input files:\n";
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
        cout << "\n=== Input File -> Lagrange Interpolation Demo ===\n";

        const string dataFile = chooseInterpolationInputFile();

        vector<long double> xData;
        vector<long double> yData;

        if (!loadCheckData(dataFile, xData, yData))
            throw runtime_error("Failed to read interpolation points from file: " + dataFile);

        if (xData.size() < 2)
            throw runtime_error("Interpolation file must contain at least 2 points.");

        cout << "Loaded " << xData.size() << " interpolation points from input file (auto-detected size).\n";

        // Interpolation and Lagrange classes (inheritance chain) in action.
        Lagrange lag(xData, yData);
        const vector<long double> interpX = lag.getX();
        const vector<long double> interpY = lag.getY();

        long double customX;
        cout << "Enter an x value to evaluate with Lagrange interpolation: ";
        cin >> customX;

        const long double customY = lag.evaluate(customX);
        cout << "Evaluated value at x=" << customX << " is y=" << customY << "\n";

        vector<pair<long double, long double>> curve = lag.evaluateRange(interpX.front(), interpX.back(), 150);

        saveDataFile("interpolation_points.dat", interpX, interpY);
        saveCurveFile("lagrange_curve.dat", curve);

        ofstream report("interpolation_report.txt");
        if (!report)
            throw runtime_error("Error creating interpolation_report.txt");

        report << fixed << setprecision(10);
        report << "Interpolation input file: " << dataFile << "\n";
        report << "Interpolation points: " << lag.pointCount() << "\n";
        report << "Evaluation at x=" << customX << ": " << customY << "\n";
        report << "Output data files:\n";
        report << "  interpolation_points.dat\n";
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

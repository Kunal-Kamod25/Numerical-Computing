#include "Matrix.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static void generateGershgorinPlot(const string &dataFile,
                                   const vector<Matrix::GershgorinDisk> &disks,
                                   const pair<long double, long double> &bounds)
{
    const string scriptFile = "plot_gershgorin.gnu";
    const string imageFile = "graph_gershgorin.png";

    ofstream gp(scriptFile);
    if (!gp)
        throw runtime_error("Error creating " + scriptFile);

    gp << "set terminal pngcairo size 1400,1000 enhanced font 'Arial,11'\n";
    gp << "set output '" << imageFile << "'\n";
    long double maxRadius = 0.0L;
    for (const auto &d : disks)
        if (d.radius > maxRadius)
            maxRadius = d.radius;

    const long double xMargin = max<long double>(1.0L, (bounds.second - bounds.first) * 0.05L);
    const long double yMargin = max<long double>(1.0L, maxRadius * 0.15L);
    const long double xMin = bounds.first - xMargin;
    const long double xMax = bounds.second + xMargin;
    const long double yMax = maxRadius + yMargin;

    gp << "set title 'Gershgorin Disks (Eigenvalue Bounds)'\n";
    gp << "set xlabel 'Real Axis'\n";
    gp << "set ylabel 'Imaginary Axis'\n";
    gp << "set grid\n";
    gp << "set size ratio -1\n";
    gp << "set key off\n";
    gp << "set border lw 1.5\n";
    gp << "set xtics out\n";
    gp << "set ytics out\n";
    gp << "set xrange [" << xMin << ":" << xMax << "]\n";
    gp << "set yrange [" << -yMax << ":" << yMax << "]\n";
    gp << "set arrow 1 from graph 0,0 to graph 1,0 nohead lc rgb 'black' dt 2\n";
    gp << "set arrow 2 from 0,graph 0 to 0,graph 1 nohead lc rgb 'black' dt 2\n";
    for (size_t i = 0; i < disks.size(); ++i)
        gp << "set label " << (i + 1) << " '" << (i + 1) << "' at " << disks[i].center << ",0 offset char 0,1 tc rgb '#d62728'\n";

    gp << "set style fill transparent solid 0.14 noborder\n";
    gp << "plot '" << dataFile << "' using 2:0:3 with circles lc rgb '#1f77b4' fs transparent solid 0.20 noborder, \\\n";
    gp << "     '" << dataFile << "' using 2:0 with points pt 7 ps 0.35 lc rgb '#d62728'\n";
    gp.close();

    if (system("gnuplot --version > /dev/null 2>&1") == 0)
    {
        const string cmd = "gnuplot " + scriptFile;
        system(cmd.c_str());
        cout << "Gershgorin plot saved to " << imageFile << "\n";

        const string openCmd = "xdg-open " + imageFile + " >/dev/null 2>&1 &";
        system(openCmd.c_str());
    }
    else
    {
        cout << "gnuplot is not installed, so the Gershgorin plot step was skipped.\n";
    }
}

int main()
{
    try
    {
        int n;
        cout << "\n=== Gershgorin Analysis ===\n";
        cout << "Enter matrix size n (n x n): ";
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
            cout << "Enter filename for square matrix A: ";
            cin >> left;
        }

        Matrix A(n, n);
        A.readFromFile(left);

        vector<Matrix::GershgorinDisk> disks = A.gershgorinDisks();
        pair<long double, long double> bounds = A.gershgorinRealBounds();

        ofstream out("gershgorin_analysis.dat");
        if (!out)
            throw runtime_error("Error creating gershgorin_analysis.dat");

        out << fixed << setprecision(10);
        out << "# index   center            radius            left_bound        right_bound\n";
        for (int i = 0; i < (int)disks.size(); i++)
        {
            const long double leftBound = disks[i].center - disks[i].radius;
            const long double rightBound = disks[i].center + disks[i].radius;
            out << setw(8) << i
                << setw(18) << disks[i].center
                << setw(18) << disks[i].radius
                << setw(18) << leftBound
                << setw(18) << rightBound << '\n';
        }

        out << "\n# real_eigenvalue_interval " << bounds.first << " " << bounds.second << '\n';
        out.close();

        cout << "Gershgorin analysis saved to gershgorin_analysis.dat\n";
        generateGershgorinPlot("gershgorin_analysis.dat", disks, bounds);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

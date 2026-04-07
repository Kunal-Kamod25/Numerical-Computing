#include "Matrix.hpp"
#include "SLE.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static void generateAndOpenSolutionPlot(const string &dataFile, const string &title, const string &graphFile)
{
    const string scriptFile = graphFile + ".gnu";
    ofstream gp(scriptFile);
    if (!gp)
        throw runtime_error("Error creating " + scriptFile);

    gp << "set terminal pngcairo size 1280,720 enhanced font 'Arial,11'\n";
    gp << "set output '" << graphFile << "'\n";
    gp << "set title '" << title << "'\n";
    gp << "set xlabel 'X (Index)'\n";
    gp << "set ylabel 'Y (Solution Value)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";
    gp << "plot '" << dataFile << "' using 1:2 with linespoints lw 2 pt 7 ps 0.6 title '" << title << "'\n";
    gp.close();

    if (system("gnuplot --version > /dev/null 2>&1") == 0)
    {
        string cmd = "gnuplot " + scriptFile;
        system(cmd.c_str());
        string openCmd = "xdg-open " + graphFile + " >/dev/null 2>&1 &";
        system(openCmd.c_str());
    }
}

static void saveResults(const string &filename, const vector<long double> &sol)
{
    ofstream out(filename);
    if (!out)
        throw runtime_error("Error creating " + filename);

    for (int i = 0; i < (int)sol.size(); i++)
        out << i << " " << sol[i] << endl;
}

int main()
{
    try
    {
        int n;
        cout << "\n=== Gaussian Elimination Solver ===\n";
        cout << "Enter Size (4, 49, or 225): ";
        cin >> n;

        string left, right;
        if (n == 225)
        {
            left = "Large_Matrix/225left.txt";
            right = "Large_Matrix/225right.txt";
        }
        else if (n == 49)
        {
            left = "Large_Matrix/49l.txt";
            right = "Large_Matrix/49r.txt";
        }
        else if (n == 4)
        {
            left = "Large_Matrix/Sl.txt";
            right = "Large_Matrix/Sr.txt";
        }
        else
        {
            cout << "Unsupported matrix size\n";
            return 0;
        }

        Matrix A(n, n);
        Matrix B(n, 1);
        A.readFromFile(left);
        B.readFromFile(right);

        SLE aug(n, n + 1);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                aug(i, j) = A(i, j);
            aug(i, n) = B(i, 0);
        }

        vector<long double> solution = aug.solve(SLE::GAUSSIAN);
        saveResults("solution_gaussian_elimination.dat", solution);

        cout << "Solution saved to solution_gaussian_elimination.dat\n";
        generateAndOpenSolutionPlot("solution_gaussian_elimination.dat", "Gaussian Elimination", "graph_gaussian_elimination.png");
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

#include "Matrix.hpp"
#include "Iterative.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

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

void saveResults(const string &filename, const vector<long double> &sol) {
    ofstream out(filename);
    if (!out) return;
    out << fixed << setprecision(10);
    for (int i = 0; i < (int)sol.size(); i++) {
        out << i << " " << sol[i] << endl;
    }
}

int main() {
    try {
        int n;
        cout << "\n=== Iterative Solver Test ===\n";
        cout << "Enter Size (4 or 225): ";
        cin >> n;

        string left, right;
        if (n == 225) {
            left = "Large_Matrix/225left.txt";
            right = "Large_Matrix/225right.txt";
        } else if (n == 49) {
            left = "Large_Matrix/49l.txt";
            right = "Large_Matrix/49r.txt";
        } else {
            left = "Large_Matrix/Sl.txt";
            right = "Large_Matrix/Sr.txt";
        }

        Matrix A(n, n);
        Matrix b(n, 1);

        auto loadFile = [&](Matrix &target, string fname, int r, int c) {
            ifstream f(fname);
            if (!f) throw runtime_error("File not found: " + fname);
            
            // Large files in this project have "rows cols" header
            if (n == 225) {
                double d1, d2;
                f >> d1 >> d2;
            }
            
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (!(f >> target(i, j))) break;
                }
            }
        };

        cout << "Loading " << left << "..." << endl;
        loadFile(A, left, n, n);
        cout << "Loading " << right << "..." << endl;
        loadFile(b, right, n, 1);

        cout << "Preparing iterative matrix once..." << endl;
        Iterative::ensureDiagonallyDominant(A);

        Jacobi jSolver(n, n + 1);
        GaussSeidel gsSolver(n, n + 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                jSolver(i, j) = A(i, j);
                gsSolver(i, j) = A(i, j);
            }
            jSolver(i, n) = b(i, 0);
            gsSolver(i, n) = b(i, 0);
        }

        cout << "Solving with Jacobi..." << endl;
        saveResults("solution_jacobi.dat", jSolver.solveIterative());
        generateAndOpenSolutionPlot("solution_jacobi.dat", "Jacobi", "graph_jacobi.png");

        cout << "Solving with Gauss-Seidel..." << endl;
        saveResults("solution_gauss_seidel.dat", gsSolver.solveIterative());
        generateAndOpenSolutionPlot("solution_gauss_seidel.dat", "Gauss-Seidel", "graph_gauss_seidel.png");

        cout << "\nFinished! Solutions saved to .dat files." << endl;

    } catch (const exception &e) {
        cerr << "ERROR: " << e.what() << endl;
    }
    return 0;
}

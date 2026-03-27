#include "Matrix.hpp"
#include "Iterative.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void saveResults(const string &filename, const vector<long double> &sol) {
    ofstream out(filename);
    if (!out) return;
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

        cout << "Enhancing diagonal dominance..." << endl;
        jSolver.makeDiagonallyDominant();
        gsSolver.makeDiagonallyDominant();

        cout << "Solving with Jacobi..." << endl;
        saveResults("solution_jacobi.dat", jSolver.solveIterative());

        cout << "Solving with Gauss-Seidel..." << endl;
        saveResults("solution_gs.dat", gsSolver.solveIterative());

        cout << "\nFinished! Solutions saved to .dat files." << endl;

    } catch (const exception &e) {
        cerr << "ERROR: " << e.what() << endl;
    }
    return 0;
}

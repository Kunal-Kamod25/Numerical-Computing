#include "Matrix.hpp"
#include "SLE.hpp"
#include "Iterative.hpp"
#include <chrono>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>

using namespace std;

namespace {

bool readIntLine(const string &prompt, int &value, bool allowEmpty = false, int defaultValue = 0) {
    cout << prompt;
    string line;
    getline(cin, line);

    if (line.empty() && allowEmpty) {
        value = defaultValue;
        return true;
    }

    stringstream ss(line);
    int temp;
    char extra;
    if (!(ss >> temp) || (ss >> extra)) {
        return false;
    }

    value = temp;
    return true;
}

bool readLongDoubleLine(const string &prompt, long double &value, bool allowEmpty = false, long double defaultValue = 0.0L) {
    cout << prompt;
    string line;
    getline(cin, line);

    if (line.empty() && allowEmpty) {
        value = defaultValue;
        return true;
    }

    stringstream ss(line);
    long double temp;
    char extra;
    if (!(ss >> temp) || (ss >> extra)) {
        return false;
    }

    value = temp;
    return true;
}

bool loadMatrixAutoFormat(Matrix &target, const string &filename, int expectedRows, int expectedCols) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Cannot open file: " + filename);
    }

    auto fillPlain = [&](istream &in) -> bool {
        for (int i = 0; i < expectedRows; i++) {
            for (int j = 0; j < expectedCols; j++) {
                if (!(in >> target(i, j))) {
                    return false;
                }
            }
        }
        return true;
    };

    long double r = 0.0L;
    long double c = 0.0L;
    streampos afterHeaderPos = streampos(-1);
    if (fin >> r >> c) {
        afterHeaderPos = fin.tellg();
        long long rr = llround(r);
        long long cc = llround(c);
        bool looksIntegral = fabsl(r - rr) < 1e-9L && fabsl(c - cc) < 1e-9L;

        if (looksIntegral && rr == expectedRows && cc >= expectedCols) {
            bool ok = true;
            for (int i = 0; i < expectedRows && ok; i++) {
                for (int j = 0; j < expectedCols; j++) {
                    if (!(fin >> target(i, j))) {
                        ok = false;
                        break;
                    }
                }
                for (long long j = expectedCols; j < cc && ok; j++) {
                    long double discard = 0.0L;
                    if (!(fin >> discard)) {
                        ok = false;
                    }
                }
            }
            if (ok) {
                return true;
            }

            // Some project files have inconsistent second header value.
            // In that case, treat header as informational and read only required entries.
            fin.clear();
            fin.seekg(afterHeaderPos);
            if (fillPlain(fin)) {
                return true;
            }

            throw runtime_error("Header/data mismatch for expected matrix size in: " + filename);
        }
    }

    fin.clear();
    fin.seekg(0);
    if (fillPlain(fin)) {
        return true;
    }

    throw runtime_error("File format mismatch for expected matrix size in: " + filename);
}

void fillAugmentedMatrix(const Matrix &A, const Matrix &B, SLE &aug, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug(i, j) = A(i, j);
        }
        aug(i, n) = B(i, 0);
    }
}

void fillIterativeMatrix(const Matrix &A, const Matrix &B, Iterative &solver, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            solver(i, j) = A(i, j);
        }
        solver(i, n) = B(i, 0);
    }
}

void swapRows(Matrix &A, Matrix &B, int r1, int r2, int n, int rhsCols) {
    if (r1 == r2) {
        return;
    }

    for (int j = 0; j < n; j++) {
        long double tmp = A(r1, j);
        A(r1, j) = A(r2, j);
        A(r2, j) = tmp;
    }

    for (int j = 0; j < rhsCols; j++) {
        long double tmp = B(r1, j);
        B(r1, j) = B(r2, j);
        B(r2, j) = tmp;
    }
}

bool tryRowReorderForDiagonalDominance(Matrix &A, Matrix &B, int n, int rhsCols) {
    for (int i = 0; i < n; i++) {
        int bestRow = i;
        long double bestVal = fabsl(A(i, i));

        for (int r = i + 1; r < n; r++) {
            long double cand = fabsl(A(r, i));
            if (cand > bestVal) {
                bestVal = cand;
                bestRow = r;
            }
        }

        swapRows(A, B, i, bestRow, n, rhsCols);
    }

    return A.isDiagonallyDominant();
}

void saveSolutionFile(const string &filename, const vector<long double> &solution) {
    ofstream out(filename);
    if (!out) {
        throw runtime_error("Failed to create output file: " + filename);
    }

    for (int i = 0; i < (int)solution.size(); i++) {
        out << i << " " << setprecision(16) << solution[i] << '\n';
    }
}

string toFileSlug(const string &name) {
    string slug;
    for (size_t i = 0; i < name.size(); i++) {
        char ch = static_cast<char>(tolower(static_cast<unsigned char>(name[i])));
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
            slug.push_back(ch);
        } else {
            slug.push_back('_');
        }
    }
    while (!slug.empty() && slug.back() == '_') {
        slug.pop_back();
    }
    return slug.empty() ? string("solution") : slug;
}

void saveNamedSolutionFile(const string &filename, const string &solverName, const vector<long double> &solution) {
    ofstream out(filename);
    if (!out) {
        throw runtime_error("Failed to create output file: " + filename);
    }

    out << "# Solver: " << solverName << '\n';
    out << "# X Y\n";
    for (int i = 0; i < (int)solution.size(); i++) {
        out << i << " " << setprecision(16) << solution[i] << '\n';
    }
}

void generateGnuplot2D(const string &dataFile, const string &solverName) {
    const string slug = toFileSlug(solverName);
    const string scriptFile = "plot_" + slug + ".gnu";
    const string imageFile = "graph_" + slug + ".png";

    ofstream gp(scriptFile);
    if (!gp) {
        throw runtime_error("Failed to create gnuplot script: " + scriptFile);
    }

    gp << "set terminal pngcairo size 1280,720 enhanced font 'Arial,11'\n";
    gp << "set output '" << imageFile << "'\n";
    gp << "set title '" << solverName << " - 2D Plot (X vs Y)'\n";
    gp << "set xlabel 'X (Index)'\n";
    gp << "set ylabel 'Y (Solution Value)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";
    gp << "plot '" << dataFile << "' using 1:2 with linespoints lw 2 pt 7 ps 0.6 title '" << solverName << "'\n";
    gp.close();

    vector<string> gnuplotCandidates;
    if (system("where gnuplot >nul 2>nul") == 0) {
        gnuplotCandidates.push_back("gnuplot");
    }

    const char *programFiles = getenv("ProgramFiles");
    if (programFiles != nullptr) {
        gnuplotCandidates.push_back(string(programFiles) + "\\gnuplot\\bin\\gnuplot.exe");
    }

    const char *programFilesX86 = getenv("ProgramFiles(x86)");
    if (programFilesX86 != nullptr) {
        gnuplotCandidates.push_back(string(programFilesX86) + "\\gnuplot\\bin\\gnuplot.exe");
    }

    int rc = 1;
    for (size_t i = 0; i < gnuplotCandidates.size(); i++) {
        const string &candidate = gnuplotCandidates[i];
        if (candidate != "gnuplot" && !filesystem::exists(candidate)) {
            continue;
        }

        string cmd;
        if (candidate == "gnuplot") {
            cmd = "cmd /C gnuplot \"" + scriptFile + "\"";
        } else {
            cmd = "cmd /C \"\"" + candidate + "\" \"" + scriptFile + "\"\"";
        }

        rc = system(cmd.c_str());
        if (rc == 0) {
            break;
        }
    }

    if (rc != 0) {
        cout << "Warning: gnuplot could not run automatically.\n";
        cout << "Install gnuplot or add it to PATH, then run: gnuplot \"" << scriptFile << "\"\n";
    } else {
        cout << "2D graph generated: " << imageFile << "\n";
    }
}

char askYesNo(const string &prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        if (line.empty()) {
            continue;
        }

        char c = static_cast<char>(tolower(static_cast<unsigned char>(line[0])));
        if (c == 'y' || c == 'n') {
            return c;
        }

        cout << "Please enter y or n.\n";
    }
}

} // namespace

int main() {
    try {
        cout << "========================================\n";
        cout << "   LINEAR SYSTEM SOLVER\n";
        cout << "========================================\n\n";

        cout << "Choose Matrix Dataset to Load:\n";
        cout << "1. Small System (Sl.txt, Sr.txt)\n";
        cout << "2. 49x49 System (49l.txt, 49r.txt)\n";
        cout << "3. 225x225 System (225left.txt, 225right.txt)\n";
        cout << "4. Enter custom filenames manually\n\n";

        int datasetChoice = 0;
        while (!readIntLine("Enter choice: ", datasetChoice) || datasetChoice < 1 || datasetChoice > 4) {
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }

        int n = 0;
        int rhsCols = 1;
        string fileA;
        string fileB;
        bool hasFileB = true;

        if (datasetChoice == 1) {
            n = 4;
            rhsCols = 1;
            fileA = "Large_Matrix/Sl.txt";
            fileB = "Large_Matrix/Sr.txt";
        } else if (datasetChoice == 2) {
            n = 49;
            rhsCols = 1;
            fileA = "Large_Matrix/49l.txt";
            fileB = "Large_Matrix/49r.txt";
        } else if (datasetChoice == 3) {
            n = 225;
            rhsCols = 1;
            fileA = "Large_Matrix/225left.txt";
            fileB = "Large_Matrix/225right.txt";
        } else {
            while (!readIntLine("\nEnter size of system (n x n): ", n) || n <= 0) {
                cout << "Invalid size. Please enter a positive integer.\n";
            }

            while (!readIntLine("Enter number of RHS columns (usually 1): ", rhsCols) || rhsCols <= 0) {
                cout << "Invalid RHS column count. Please enter a positive integer.\n";
            }

            if (rhsCols != 1) {
                cout << "Note: Current solvers support one RHS column. Using first RHS column only.\n";
                rhsCols = 1;
            }

            cout << "Enter filename for coefficient matrix A: ";
            getline(cin, fileA);

            char hasB = askYesNo("Do you have a file for the RHS matrix B? (y/n): ");
            hasFileB = (hasB == 'y');
            if (hasFileB) {
                cout << "Enter filename for RHS matrix B: ";
                getline(cin, fileB);
            }
        }

        Matrix A(n, n);
        Matrix B(n, rhsCols);

        cout << "\nReading coefficient matrix A from " << fileA << "...\n";
        loadMatrixAutoFormat(A, fileA, n, n);

        if (hasFileB) {
            cout << "Reading RHS matrix B from " << fileB << "...\n";
            loadMatrixAutoFormat(B, fileB, n, rhsCols);
        } else {
            char manual = askYesNo("Do you want to type the values manually? (y = yes, n = auto-fill with 1s): ");
            if (manual == 'y') {
                cout << "Enter " << n * rhsCols << " values for B (row-major order):\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < rhsCols; j++) {
                        long double x = 0.0L;
                        while (!readLongDoubleLine("", x)) {
                            cout << "Invalid number, try again: ";
                        }
                        B(i, j) = x;
                    }
                }
            } else {
                cout << "\nAuto-filling RHS vector B with 1.0s so the system can be solved...\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < rhsCols; j++) {
                        B(i, j) = 1.0L;
                    }
                }
            }
        }

        cout << "\n========================================\n";
        cout << "   MATRIX PROPERTIES\n";
        cout << "========================================\n";
        A.displayProperties();

        bool matrixIsDD = A.isDiagonallyDominant();
        bool canMakeDDByReorder = false;
        if (!matrixIsDD) {
            Matrix testA = A;
            Matrix testB = B;
            canMakeDDByReorder = tryRowReorderForDiagonalDominance(testA, testB, n, rhsCols);
            cout << "Can be made diagonally dominant by row reordering: "
                 << (canMakeDDByReorder ? "yes" : "no") << "\n";
        }

        cout << "\nCreating augmented matrix [A|B]...\n";
        SLE baseAugmented(n, n + 1);
        fillAugmentedMatrix(A, B, baseAugmented, n);
        (void)baseAugmented;
        cout << "Augmented matrix created successfully.\n";

        while (true) {
            cout << "\n========================================\n";
            cout << "   LINEAR SYSTEM SOLVER MENU\n";
            cout << "========================================\n";
            cout << "Choose a solving method:\n\n";
            cout << "  DIRECT METHODS:\n";
            cout << "  1. Gaussian Elimination with Pivoting\n";
            cout << "  2. LU Decomposition (Doolittle)\n";
            cout << "  3. LU Decomposition (Crout)\n";
            cout << "  4. LU Decomposition (Cholesky)\n\n";
            cout << "  ITERATIVE METHODS:\n";
            cout << "  5. Jacobi Method\n";
            cout << "  6. Gauss-Seidel Method\n\n";
            cout << "  0. Exit\n";
            cout << "========================================\n";

            int solveChoice = -1;
            while (!readIntLine("Enter choice: ", solveChoice) || solveChoice < 0 || solveChoice > 6) {
                cout << "Invalid choice. Please enter a number from 0 to 6.\n";
            }

            if (solveChoice == 0) {
                break;
            }

            vector<long double> solution;
            string solverName;
            auto start = chrono::high_resolution_clock::now();

            if (solveChoice >= 1 && solveChoice <= 4) {
                SLE solver(n, n + 1);
                fillAugmentedMatrix(A, B, solver, n);

                cout << "\nSolving using selected direct method...\n";
                if (solveChoice == 1) {
                    solverName = "Gaussian Elimination";
                    solution = solver.solve(SLE::GAUSSIAN);
                } else if (solveChoice == 2) {
                    solverName = "LU Doolittle";
                    solution = solver.solve(SLE::LU_METHOD, SLE::DOOLITTLE);
                } else if (solveChoice == 3) {
                    solverName = "LU Crout";
                    solution = solver.solve(SLE::LU_METHOD, SLE::CROUT);
                } else {
                    solverName = "LU Cholesky";
                    solution = solver.solve(SLE::LU_METHOD, SLE::CHOLESKY);
                }
            } else {
                int maxIter = 1000;
                long double tol = 1e-10L;

                if (solveChoice == 5) {
                    cout << "\n========================================\n";
                    cout << "   JACOBI ITERATIVE METHOD\n";
                    cout << "========================================\n";
                } else {
                    cout << "\n========================================\n";
                    cout << "   GAUSS-SEIDEL ITERATIVE METHOD\n";
                    cout << "========================================\n";
                }

                while (!readIntLine("Enter maximum iterations (default 1000): ", maxIter, true, 1000) || maxIter <= 0) {
                    cout << "Invalid iteration count. Enter a positive integer.\n";
                }
                while (true) {
                    if (!readLongDoubleLine("Enter tolerance (default 1e-10): ", tol, true, 1e-10L) || tol <= 0.0L) {
                        cout << "Invalid tolerance. Enter a positive number.\n";
                        continue;
                    }

                    if (tol >= 1.0L) {
                        cout << "Warning: tolerance >= 1 can cause very early stopping and inaccurate results.\n";
                        char useLargeTol = askYesNo("Use this tolerance anyway? (y/n): ");
                        if (useLargeTol == 'n') {
                            continue;
                        }
                    }
                    break;
                }

                cout << "\nSolving using " << (solveChoice == 5 ? "Jacobi" : "Gauss-Seidel") << " Method...\n";
                Matrix AIter = A;
                Matrix BIter = B;

                if (!matrixIsDD) {
                    cout << "Warning: Matrix is NOT diagonally dominant. Convergence is not guaranteed!\n";
                    if (canMakeDDByReorder) {
                        char applyReorder = askYesNo("Matrix can be reordered to become diagonally dominant. Apply row reordering for iterative method? (y/n): ");
                        if (applyReorder == 'y') {
                            (void)tryRowReorderForDiagonalDominance(AIter, BIter, n, rhsCols);
                            cout << "Row reordering applied for iterative solve.\n";
                        }
                    } else {
                        cout << "Matrix cannot be made diagonally dominant by simple row reordering.\n";
                    }
                }

                if (solveChoice == 5) {
                    solverName = "Jacobi";
                    Jacobi jacobi(n, n + 1);
                    fillIterativeMatrix(AIter, BIter, jacobi, n);
                    jacobi.setMaxIterations(maxIter);
                    jacobi.setTolerance(tol);
                    solution = jacobi.solveIterative();
                } else {
                    solverName = "Gauss-Seidel";
                    GaussSeidel gs(n, n + 1);
                    fillIterativeMatrix(AIter, BIter, gs, n);
                    gs.setMaxIterations(maxIter);
                    gs.setTolerance(tol);
                    solution = gs.solveIterative();
                }
            }

            auto end = chrono::high_resolution_clock::now();
            double elapsedMs = chrono::duration<double, milli>(end - start).count();

            cout << "\n========================================\n";
            cout << "   SOLUTION RESULTS\n";
            cout << "========================================\n";
            cout << "System solved successfully!\n";
            cout << fixed << setprecision(2) << "Time taken: " << elapsedMs << " ms\n\n";

            cout << "Solution vector:\n";
            cout << setprecision(10);
            for (int i = 0; i < (int)solution.size(); i++) {
                cout << "  x[" << i << "] = " << solution[i] << "\n";
            }

            saveSolutionFile("solution.dat", solution);
            const string namedFile = "solution_" + toFileSlug(solverName) + ".dat";
            saveNamedSolutionFile(namedFile, solverName, solution);
            cout << "\nSolution saved to 'solution.dat'\n";
            cout << "Named solution saved to '" << namedFile << "'\n";

            generateGnuplot2D(namedFile, solverName);

            char again = askYesNo("\nTry another solver method? (y/n): ");
            if (again == 'n') {
                break;
            }
        }

        cout << "\n========================================\n";
        cout << "Program completed successfully!\n";
        cout << "========================================\n";
    } catch (const exception &e) {
        cerr << "\nError: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

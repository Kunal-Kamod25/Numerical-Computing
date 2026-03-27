#include "Matrix.hpp"
#include "SLE.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

/**
 * =====================================================
 * MAIN PROGRAM - LINEAR SYSTEM SOLVER
 * =====================================================
 * Supports multiple solving methods:
 *   1. Gaussian Elimination (Direct)
 *   2. LU Decomposition - Doolittle (Direct)
 *   3. LU Decomposition - Crout (Direct)
 *   4. LU Decomposition - Cholesky (Direct, for symmetric positive definite)
 *   5. Jacobi Method (Iterative)
 *   6. Gauss-Seidel Method (Iterative)
 */

void displayMenu() {
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
    cout << "Enter choice: ";
}

// ================= SOLVER HELPER FUNCTIONS =================

vector<long double> runGaussianMethod(SLE& solver) {
    cout << "   GAUSSIAN ELIMINATION\n";
    cout << "========================================\n";
    cout << "Solving using Gaussian Elimination with Pivoting...\n";
    return solver.solve(SLE::GAUSSIAN);
}

vector<long double> runLUMethods(SLE& solver, int choice) {
    if (choice == 2) {
        cout << "   LU DECOMPOSITION (DOOLITTLE)\n";
        cout << "========================================\n";
        cout << "Solving using LU Decomposition (Doolittle method)...\n";
        return solver.solve(SLE::LU_METHOD, SLE::DOOLITTLE);
    } else if (choice == 3) {
        cout << "   LU DECOMPOSITION (CROUT)\n";
        cout << "========================================\n";
        cout << "Solving using LU Decomposition (Crout method)...\n";
        return solver.solve(SLE::LU_METHOD, SLE::CROUT);
    } else {
        cout << "   LU DECOMPOSITION (CHOLESKY)\n";
        cout << "========================================\n";
        cout << "Solving using LU Decomposition (Cholesky method)...\n";
        cout << "Note: Matrix must be symmetric positive definite!\n";
        return solver.solve(SLE::LU_METHOD, SLE::CHOLESKY);
    }
}

vector<long double> runIterativeMethods(SLE& solver, int choice) {
    int max_iter;
    long double tol;
    
    if (choice == 5) cout << "   JACOBI ITERATIVE METHOD\n";
    else cout << "   GAUSS-SEIDEL ITERATIVE METHOD\n";
    cout << "========================================\n";
    
    cout << "Enter maximum iterations (default 1000): ";
    cin >> max_iter;
    cout << "Enter tolerance (default 1e-10): ";
    cin >> tol;
    
    if (choice == 5) {
        cout << "\nSolving using Jacobi Method...\n";
        return solver.solve(SLE::JACOBI, SLE::DOOLITTLE, max_iter, tol);
    } else {
        cout << "\nSolving using Gauss-Seidel Method...\n";
        return solver.solve(SLE::GAUSS_SEIDEL, SLE::DOOLITTLE, max_iter, tol);
    }
}

int main()
{
    try
    {
        // ================= INPUT SYSTEM MATRICES =================
        cout << "========================================\n";
        cout << "   LINEAR SYSTEM SOLVER\n";
        cout << "========================================\n\n";
        
        cout << "Choose Matrix Dataset to Load:\n";
        cout << "1. 3x3 System (Sl.txt, Sr.txt)\n";
        cout << "2. 49x49 System (49l.txt, 49r.txt)\n";
        cout << "3. 225x225 System (225left.txt, 225right.txt)\n";
        cout << "4. Enter custom filenames manually\n\n";
        cout << "Enter choice: ";
        
        int datasetChoice;
        cin >> datasetChoice;
        
        int n = 0, m = 1;
        string fileA, fileB;
        
        if (datasetChoice == 1) {
            n = 3; m = 1;
            fileA = "Large_Matrix/Sl.txt"; 
            fileB = "Large_Matrix/Sr.txt";
        } else if (datasetChoice == 2) {
            n = 49; m = 1;
            fileA = "Large_Matrix/49l.txt"; 
            fileB = "Large_Matrix/49r.txt";
        } else if (datasetChoice == 3) {
            n = 225; m = 1;
            fileA = "Large_Matrix/225left.txt"; 
            fileB = "Large_Matrix/225right.txt";
        } else {
            cout << "\nEnter size of system (n x n): ";
            cin >> n;
            cout << "Enter number of RHS columns (usually 1): ";
            cin >> m;
            cout << "Enter filename for coefficient matrix A: ";
            cin >> fileA;
            
            char hasRHS;
            cout << "Do you have a file for the RHS matrix B? (y/n): ";
            cin >> hasRHS;
            if (hasRHS == 'y' || hasRHS == 'Y') {
                cout << "Enter filename for RHS matrix B: ";
                cin >> fileB;
            } else {
                fileB = ""; // Trigger manual input
            }
        }

        // ================= CREATE MATRICES =================
        cout << "\nReading coefficient matrix A from " << fileA << "...\n";
        ifstream finA(fileA);
        if (!finA) throw runtime_error("Cannot open " + fileA);
        if (datasetChoice >= 1 && datasetChoice <= 3) {
            int dummyRows, dummyCols;
            finA >> dummyRows >> dummyCols; // Skip header
        }
        Matrix A(n, n);
        A.readFromFile(finA);
        finA.close();
        
        Matrix B(n, m);
        if (!fileB.empty()) {
            cout << "Reading RHS matrix B from " << fileB << "...\n";
            ifstream finB(fileB);
            if (!finB) throw runtime_error("Cannot open " + fileB);
            if (datasetChoice >= 1 && datasetChoice <= 3) {
                int dummyRows, dummyCols;
                finB >> dummyRows >> dummyCols; // Skip header
            }
            B.readFromFile(finB);
            finB.close();
        } else {
            char autoFill;
            cout << "Do you want to type the values manually? (y = yes, n = auto-fill with 1s): ";
            cin >> autoFill;
            if (autoFill == 'y' || autoFill == 'Y') {
                cout << "\n--- Manual RHS Input ---\n";
                cout << "Please type the " << (n * m) << " values for your RHS matrix B, pressing Enter after each:\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cout << "B[" << i << "][" << j << "]: ";
                        long double val;
                        cin >> val;
                        B(i, j) = val;
                    }
                }
            } else {
                cout << "\nAuto-filling RHS vector B with 1.0s so the system can be solved...\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        B(i, j) = 1.0;
                    }
                }
            }
        }

        // ================= DISPLAY PROPERTIES =================
        cout << "\n========================================\n";
        cout << "   MATRIX PROPERTIES\n";
        cout << "========================================\n";
        A.displayProperties();

        // ================= CREATE AUGMENTED MATRIX =================
        cout << "\nCreating augmented matrix [A|B]...\n";
        SLE Aug(n, n + m);

        // Copy A into left part of augmented matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Aug(i, j) = A(i, j);

        // Copy B into right part of augmented matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Aug(i, n + j) = B(i, j);

        cout << "Augmented matrix created successfully.\n";

        // ================= SOLVER MENU LOOP =================
        int choice;
        bool exitProgram = false;

        while (!exitProgram) {
            displayMenu();
            cin >> choice;

            if (choice == 0) {
                cout << "\nExiting program. Goodbye!\n";
                exitProgram = true;
                continue;
            }

            // Create a copy of augmented matrix for solving (direct methods modify it)
            SLE solver = Aug;
            vector<long double> solution;
            
            // Start timer
            auto start = high_resolution_clock::now();

            // ================= SOLVE BASED ON CHOICE =================
            cout << "\n========================================\n";
            if (choice == 1) {
                solution = runGaussianMethod(solver);
            } else if (choice >= 2 && choice <= 4) {
                solution = runLUMethods(solver, choice);
            } else if (choice == 5 || choice == 6) {
                solution = runIterativeMethods(solver, choice);
            } else {
                cout << "Invalid choice! Please try again.\n";
                continue;
            }

            // Stop timer
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            // ================= DISPLAY RESULTS =================
            cout << "\n========================================\n";
            cout << "   SOLUTION RESULTS\n";
            cout << "========================================\n";
            cout << "System solved successfully!\n";
            cout << "Time taken: " << duration.count() / 1000.0 << " ms\n\n";

            // Display first few and last few solutions if large
            if (solution.size() <= 20) {
                cout << "Solution vector:\n";
                for (size_t i = 0; i < solution.size(); i++) {
                    cout << "  x[" << i << "] = " << fixed << setprecision(10) 
                         << solution[i] << "\n";
                }
            } else {
                cout << "Solution vector (showing first 5 and last 5):\n";
                for (int i = 0; i < 5; i++) {
                    cout << "  x[" << i << "] = " << fixed << setprecision(10) 
                         << solution[i] << "\n";
                }
                cout << "  ...\n";
                for (size_t i = solution.size() - 5; i < solution.size(); i++) {
                    cout << "  x[" << i << "] = " << fixed << setprecision(10) 
                         << solution[i] << "\n";
                }
            }

            // ================= SAVE SOLUTION =================
            ofstream out("solution.dat");
            if (!out) throw runtime_error("Error creating solution.dat");
            
            for (size_t i = 0; i < solution.size(); i++)
                out << i << " " << setprecision(15) << solution[i] << endl;
            out.close();
            
            cout << "\nSolution saved to 'solution.dat'\n";

            // Ask if user wants to try another method
            char again;
            cout << "\nTry another solver method? (y/n): ";
            cin >> again;
            if (again != 'y' && again != 'Y') {
                exitProgram = true;
            }
        }

        cout << "\n========================================\n";
        cout << "Program completed successfully!\n";
        cout << "========================================\n";
    }
    catch (const exception &e)
    {
        cout << "\n========================================\n";
        cout << "   ERROR\n";
        cout << "========================================\n";
        cout << "Error: " << e.what() << endl;
        cout << "========================================\n";
        return 1;
    }

    return 0;
}

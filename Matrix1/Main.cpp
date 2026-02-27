#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        int n;
        cout << "Enter size of system: ";
        cin >> n;

        int m;
        cout << "Enter number of RHS columns: ";
        cin >> m;

        // ================= CREATE MATRICES =================
        Matrix A(n, n);
        Matrix B(n, m);

        // ================= READ FROM FILE =================
        A.readFromFile("225left.txt");
        B.readFromFile("225right.txt");

        // ================= CREATE AUGMENTED MATRIX =================
        Matrix Aug(n, n + m);

        // Copy A into left part
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Aug.mat[i][j] = A.mat[i][j];

        // Copy B into right part
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Aug.mat[i][n + j] = B.mat[i][j];

        // ================= SOLVING =================
        Matrix solution;

        cout << "\nTrying WITHOUT pivoting...\n";

        try
        {
            // Matrix temp = Aug uses copy constructor
            // this is a DEEP COPY — temp.mat is brand new, Aug.mat is untouched
            // so when solveWithoutPivot() modifies temp, Aug stays the same
            // this lets us try again with pivot using the original Aug
            Matrix temp = Aug;
            solution = temp.solveWithoutPivot();
            cout << "Solved WITHOUT pivoting.\n";
        }
        catch (const exception &e)
        {
            cout << "Without pivoting failed: " << e.what() << endl;
            cout << "Switching to partial pivoting...\n";

            // again deep copy of Aug — safe because of how vector copies work
            Matrix temp = Aug;
            solution = temp.solveWithPivot();
            cout << "Solved WITH pivoting.\n";
        }

        // ================= DEMO: * and / operators =================
        // just showing how to use them if you have two same-size matrices
        // A * A  = matrix multiplication
        // A / A  = element-wise division (diagonal must be non-zero)
        try
        {
            Matrix AA = A * A;
            cout << "A * A computed successfully.\n";

            // element-wise A / A would give 1s if no zeros on diagonal
            // Matrix AD = A / A;
            // cout << "A / A computed successfully.\n";
        }
        catch (const exception &e)
        {
            cout << "Operator demo error: " << e.what() << endl;
        }

        // ================= SAVE SOLUTION =================
        solution.saveSolution("solution.dat");
        cout << "Solution saved to solution.dat\n";

        // ================= GNUPLOT =================
        system("gnuplot plot.gnu_graph");
    }
    catch (const exception &e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
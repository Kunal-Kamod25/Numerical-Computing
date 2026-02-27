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
        A.readFromFile("49l.txt");
        B.readFromFile("49r.txt");

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
                Matrix temp = Aug;
                solution = temp.solveWithoutPivot();
                cout << "Solved WITHOUT pivoting.\n";
            }
            catch (const exception &e)
            {
                cout << "Without pivoting failed: " << e.what() << endl;
                cout << "Switching to partial pivoting...\n";

                Matrix temp = Aug;
                solution = temp.solveWithPivot();
                cout << "Solved WITH pivoting.\n";
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
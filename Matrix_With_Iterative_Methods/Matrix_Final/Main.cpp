#include "Matrix.hpp"
#include "SLE.hpp"
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
        A.readFromFile("Large_Matrix/Sl.txt");
        B.readFromFile("Large_Matrix/Sr.txt");

        // ================= DISPLAY PROPERTIES =================
        cout << "\nChecking matrix properties...";
        A.displayProperties();

        // ================= CREATE AUGMENTED MATRIX =================
        SLE Aug(n, n + m);

        // Copy A into left part
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Aug(i, j) = A(i, j);

        // Copy B into right part
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Aug(i, n + j) = B(i, j);

        // ================= SOLVING =================
        cout << "\nSolving using Gaussian Elimination...\n";
        vector<long double> solution = Aug.solve(SLE::GAUSSIAN);
        cout << "Solved successfully.\n";
            

        // ================= SAVE SOLUTION =================
        ofstream out("solution.dat");
        if (!out) throw runtime_error("Error creating solution.dat");
        for (int i = 0; i < (int)solution.size(); i++)
            out << i << " " << solution[i] << endl;
        out.close();
        
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
#include "Matrix.hpp"  // including our matrix header file
#include <fstream>      // for writing solution file
#include <cstdlib>      // for system() function

using namespace std;

int main()
{
    int n;  // variable to store size of system

    cout << "Enter size of system: "; 
    cin >> n;  // user enters n (example 500)

    Matrix A(n, n);   // create matrix A (left side)
    Matrix B(n, 1);   // create matrix B (right side column)

    A.readFromFile("A.txt");
    B.readFromFile("B.txt");

    // Create augmented matrix [A | B]
    Matrix Aug(n, n + 1);  // n rows and n+1 columns

    // copying A and B into augmented matrix
    for (int i = 0; i < n; i++)
    {
        // copy A part
        for (int j = 0; j < n; j++)
            Aug.mat[i][j] = A.mat[i][j];

        // copy B part (last column)
        Aug.mat[i][n] = B.mat[i][0];
    }

    cout << "\nSolving WITHOUT Pivoting:\n";

    Matrix sol1 = Aug;  // copy constructor used here
    sol1 = sol1.solveWithoutPivot();  // solving
    sol1.display();  // printing solution

    cout << "\nSolving WITH Pivoting:\n";

    Matrix sol2 = Aug;  // again copy constructor used
    sol2 = sol2.solveWithPivot();  // solving with pivot
    sol2.display();  // printing solution

    // ==============================
    // GNU PLOT SECTION STARTS HERE
    // ==============================

    ofstream outfile("solution.dat");  // file to store results

    // writing solution with pivot to file
    for (int i = 0; i < n; i++)
    {
        // writing index and solution value
        outfile << i + 1 << " " << sol2.mat[i][0] << endl;
    }

    outfile.close();  // close file

    // creating gnuplot command file
    ofstream plotfile("plot.gnu");

    plotfile << "set title 'Solution of Linear System'\n";
    plotfile << "set xlabel 'Variable Index'\n";
    plotfile << "set ylabel 'Solution Value'\n";
    plotfile << "plot 'solution.dat' using 1:2 with linespoints\n";
    plotfile << "pause -1\n";

    plotfile.close();  // close plot file

    // run gnuplot automatically
    system("gnuplot plot.gnu");

    return 0;  // program ends
}
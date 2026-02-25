#include "Matrix.hpp"   //contains Gaussian elimination functions
#include <fstream>      // for file handling
#include <cstdlib>      // for system() command to run gnuplot script
#include <iostream>  

using namespace std;

int main()
{
    try
    {
        int n;  // size of the linear system (number of equations)

        // asking user to enter size
        cout << "Enter size of system: ";
        cin >> n;

        // creating coefficient matrix A (n x n)
        Matrix A(n, n);

        // creating RHS matrix B (n x 1)
        Matrix B(n, 1);

        // reading matrix data from files
        // make sure A.txt and B.txt exist in same folder
        A.readFromFile("A.txt");
        B.readFromFile("B.txt");

        // creating augmented matrix [A | B]
        // it will have n rows and n+1 columns
        Matrix Aug(n, n + 1);

        // copying A and B into augmented matrix manually
        // this loop basically forms [A | B]
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                Aug.mat[i][j] = A.mat[i][j];   // copying A values

            Aug.mat[i][n] = B.mat[i][0];       // putting B in last column
        }

        cout << "\nSolving WITHOUT Pivoting:\n";

        // making a copy of augmented matrix
        // so original Aug does not change
        Matrix sol1 = Aug;

        // solving using normal Gaussian elimination
        // this may fail if pivot element becomes zero
        sol1 = sol1.solveWithoutPivot();

        // printing solution
        sol1.display();

        cout << "\nSolving WITH Pivoting:\n";

        // again copying original augmented matrix
        Matrix sol2 = Aug;

        // solving using partial pivoting (safer and more stable)
        sol2 = sol2.solveWithPivot();

        // displaying final solution
        sol2.display();

        // saving solution in file (used for plotting)
        sol2.saveSolution("solution.dat");

        // running gnuplot script automatically
        system("gnuplot plot.gnu");
    }
    catch (const exception &e)
    {
        // if any error occurs (like zero pivot), it will come here
        cout << "\nError occurred: " << e.what() << endl;
        cout << "Check your matrix values or try pivoting method.\n";
    }

    // program finished successfully
    return 0;
}
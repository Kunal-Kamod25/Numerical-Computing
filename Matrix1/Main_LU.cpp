#include "Matrix.hpp"
#include "LU.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    int n;

    cout<<"Enter size of system: ";
    cin>>n;

    Matrix A(n,n);
    Matrix B(n,1);

    // ================= READ FILES =================
    if(n==49)
    {
        A.readFromFile("Large_Matrix/49l.txt");
        B.readFromFile("Large_Matrix/49r.txt");
    }
    else if(n==225)
    {
        A.readFromFile("Large_Matrix/225left.txt");
        B.readFromFile("Large_Matrix/225right.txt");
    }
    else if(n==4)
    {
        A.readFromFile("Large_Matrix/Sl.txt");
        B.readFromFile("Large_Matrix/Sr.txt");
    }
    else
    {
        cout<<"Unsupported matrix size\n";
        return 0;
    }
    ofstream file("LU_Solution_File.dat");
    cout<<fixed<<setprecision(6);
    file<<fixed<<setprecision(6);

    int choice;
    cout << "\nChoose LU Decomposition method:\n";
    cout << "1. Doolittle\n";
    cout << "2. Crout\n";
    cout << "3. Cholesky\n";
    cout << "Enter choice (1-3): ";
    cin >> choice;

    LU lu(n);

    if (choice == 1) {
        // DOOLITTLE
        try {
            cout << "\nSolving using Doolittle...\n";
            lu.doolittle(A);
            vector<long double> solution = lu.solve(B);
            file << "==== DOOLITTLE METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
        } catch (const exception &e) {
            cout << "Doolittle failed: " << e.what() << endl;
        }
    } else if (choice == 2) {
        // CROUT
        try {
            cout << "\nSolving using Crout...\n";
            lu.crout(A);
            vector<long double> solution = lu.solve(B);
            file << "==== CROUT METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
        } catch (const exception &e) {
            cout << "Crout failed: " << e.what() << endl;
        }
    } else if (choice == 3) {
        // CHOLESKY
        try {
            cout << "\nSolving using Cholesky...\n";
            lu.cholesky(A);
            vector<long double> solution = lu.solve(B);
            file << "==== CHOLESKY METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
        } catch (const exception &e) {
            cout << "Cholesky failed: " << e.what() << endl;
        }
    }

    file.close();

    cout<<"\nSolution stored in LU_Solution_File.dat\n";

    system("gnuplot plot_lu.gnu");

    return 0;
}
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

    // DOOLITTLE
    try
    {
        Matrix temp = A;
        LU lu(n);

        cout<<"\nSolving using Doolittle\n";

        lu.doolittle(temp);
        Matrix solution = lu.solve(B);

        file<<"==== DOOLITTLE METHOD ====\n";
        for(int i=0;i<n;i++)
        {
            cout<<"x"<<setw(3)<<i+1<<" = "<<setw(12)<<solution.mat[i][0]<<endl;
            file<<"x"<<i+1<<" = "<<solution.mat[i][0]<<endl;
        }

        file<<"\n";
    }
    catch(const exception &e)
    {
        cout<<"Doolittle failed: "<<e.what()<<endl;
        file<<"==== DOOLITTLE FAILED ====\n\n";
    }

    // CROUT
    try
    {
        Matrix temp = A;
        LU lu(n);

        cout<<"\nSolving using Crout\n";

        lu.crout(temp);
        Matrix solution = lu.solve(B);

        file<<"==== CROUT METHOD ====\n";
        for(int i=0;i<n;i++)
        {
            cout<<"x"<<setw(3)<<i+1<<" = "<<setw(12)<<solution.mat[i][0]<<endl;
            file<<"x"<<i+1<<" = "<<solution.mat[i][0]<<endl;
        }
        file<<"\n";
    }
    catch(const exception &e)
    {
        cout<<"Crout failed: "<<e.what()<<endl;
        file<<"==== CROUT FAILED ====\n\n";
    }

    // CHOLESKY
    try
    {
        Matrix temp = A;
        LU lu(n);

        cout<<"\nSolving using Cholesky\n";

        lu.cholesky(temp);
        Matrix solution = lu.solve(B);

        file<<"==== CHOLESKY METHOD ====\n";
        for(int i=0;i<n;i++)
        {
            cout<<"x"<<setw(3)<<i+1<<" = "<<setw(12)<<solution.mat[i][0]<<endl;
            file<<"x"<<i+1<<" = "<<solution.mat[i][0]<<endl;
        }
        file<<"\n";
    }
    catch(const exception &e)
    {
        cout<<"Cholesky failed: "<<e.what()<<endl;
        file<<"==== CHOLESKY FAILED (Matrix not SPD) ====\n\n";
    }

    file.close();

    cout<<"\nSolution stored in LU_Solution_File.dat\n";

    system("gnuplot plot_lu.gnu");

    return 0;
}
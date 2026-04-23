#include "Matrix.hpp"
#include "LU.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

static void savePlotData(const string &filename, const vector<long double> &solution)
{
    ofstream out(filename);
    if (!out)
        throw runtime_error("Error creating " + filename);

    out << fixed << setprecision(10);
    for (int i = 0; i < (int)solution.size(); i++)
        out << i << " " << solution[i] << '\n';
}

static void generateAndOpenSolutionPlot(const string &dataFile, const string &title, const string &graphFile)
{
    const string scriptFile = graphFile + ".gnu";
    ofstream gp(scriptFile);
    if (!gp)
        throw runtime_error("Error creating " + scriptFile);

    gp << "set terminal pngcairo size 1280,720 enhanced font 'Arial,11'\n";
    gp << "set output '" << graphFile << "'\n";
    gp << "set title '" << title << "'\n";
    gp << "set xlabel 'X (Index)'\n";
    gp << "set ylabel 'Y (Solution Value)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";
    gp << "plot '" << dataFile << "' using 1:2 with linespoints lw 2 pt 7 ps 0.6 title '" << title << "'\n";
    gp.close();

    if (system("gnuplot --version > /dev/null 2>&1") == 0)
    {
        string cmd = "gnuplot " + scriptFile;
        system(cmd.c_str());
        string openCmd = "xdg-open " + graphFile + " >/dev/null 2>&1 &";
        system(openCmd.c_str());
    }
}

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
    vector<long double> solution;
    string method_name;

    if (choice == 1) {
        // DOOLITTLE
        try {
            cout << "\nSolving using Doolittle...\n";
            lu.doolittle(A);
            solution = lu.solve(B);
            method_name = "Doolittle";
            savePlotData("lu_solution_doolittle.dat", solution);
            file << "==== DOOLITTLE METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
            generateAndOpenSolutionPlot("lu_solution_doolittle.dat", "LU Doolittle", "graph_lu_doolittle.png");
        } catch (const exception &e) {
            cout << "Doolittle failed: " << e.what() << endl;
        }
    } else if (choice == 2) {
        // CROUT
        try {
            cout << "\nSolving using Crout...\n";
            lu.crout(A);
            solution = lu.solve(B);
            method_name = "Crout";
            savePlotData("lu_solution_crout.dat", solution);
            file << "==== CROUT METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
            generateAndOpenSolutionPlot("lu_solution_crout.dat", "LU Crout", "graph_lu_crout.png");
        } catch (const exception &e) {
            cout << "Crout failed: " << e.what() << endl;
        }
    } else if (choice == 3) {
        // CHOLESKY
        try {
            cout << "\nSolving using Cholesky...\n";
            lu.cholesky(A);
            solution = lu.solve(B);
            method_name = "Cholesky";
            savePlotData("lu_solution_cholesky.dat", solution);
            file << "==== CHOLESKY METHOD ====\n";
            for (int i = 0; i < n; i++) file << "x" << i + 1 << " = " << solution[i] << endl;
            cout << "Solution saved to LU_Solution_File.dat\n";
            generateAndOpenSolutionPlot("lu_solution_cholesky.dat", "LU Cholesky", "graph_lu_cholesky.png");
        } catch (const exception &e) {
            cout << "Cholesky failed: " << e.what() << endl;
        }
    }

    file.close();

    cout<<"\nSolution stored in LU_Solution_File.dat\n";

    system("gnuplot plot_lu.gnu");

    return 0;
}
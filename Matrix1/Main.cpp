#include "Matrix.hpp"
#include "SLE.hpp"
#include "Iterative.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

static vector<fs::path> listTextFiles(const fs::path &folder)
{
    vector<fs::path> files;

    if (!fs::exists(folder) || !fs::is_directory(folder))
        return files;

    for (const auto &entry : fs::directory_iterator(folder))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
            files.push_back(entry.path());
    }

    sort(files.begin(), files.end());
    return files;
}

static bool fileFitsMatrixShape(const fs::path &filePath, int rows, int cols, bool requireExactCols)
{
    ifstream fin(filePath);
    if (!fin)
        return false;

    vector<long double> values;
    long double value;
    while (fin >> value)
        values.push_back(value);

    const size_t expected = static_cast<size_t>(rows) * static_cast<size_t>(cols);

    if (values.size() == expected)
        return true;

    if (values.size() == expected + 2 && static_cast<int>(values[0]) == rows)
        return true;

    if (values.size() >= 2)
    {
        const int headerRows = static_cast<int>(values[0]);
        const int headerCols = static_cast<int>(values[1]);
        if (headerRows == rows &&
            (requireExactCols ? headerCols == cols : headerCols >= cols) &&
            values.size() == 2 + static_cast<size_t>(rows) * static_cast<size_t>(cols))
            return true;
    }

    return false;
}

static vector<fs::path> filterFilesForShape(const vector<fs::path> &files, int rows, int cols, bool requireExactCols)
{
    vector<fs::path> filtered;
    for (const auto &file : files)
        if (fileFitsMatrixShape(file, rows, cols, requireExactCols))
            filtered.push_back(file);
    return filtered;
}

static int chooseFileIndex(const vector<fs::path> &files, const string &prompt)
{
    while (true)
    {
        cout << prompt << endl;
        for (size_t i = 0; i < files.size(); ++i)
            cout << "  " << (i + 1) << ". " << files[i].filename().string() << endl;

        cout << "Enter choice (1-" << files.size() << "): ";

        int choice = 0;
        if (cin >> choice && choice >= 1 && choice <= (int)files.size())
            return choice - 1;

        cout << "Invalid choice. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static Matrix loadMatrixFlexible(const fs::path &filePath, int rows, int cols)
{
    ifstream fin(filePath);
    if (!fin)
        throw runtime_error("Error opening file: " + filePath.string());

    vector<long double> values;
    long double value;
    while (fin >> value)
        values.push_back(value);

    const size_t expected = static_cast<size_t>(rows) * static_cast<size_t>(cols);

    size_t startIndex = 0;
    if (values.size() == expected + 2 &&
        static_cast<int>(values[0]) == rows &&
        static_cast<int>(values[1]) == cols)
    {
        startIndex = 2;
    }

    if (values.size() < expected + startIndex)
        throw runtime_error("File does not contain enough values: " + filePath.string());

    Matrix result(rows, cols);
    size_t idx = startIndex;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (idx >= values.size())
                throw runtime_error("File ended early: " + filePath.string());
            result(i, j) = values[idx++];
        }
    }

    return result;
}

static void saveVectorSolution(const string &filename, const vector<long double> &solution)
{
    ofstream out(filename);
    if (!out)
        throw runtime_error("Error creating " + filename);

    for (int i = 0; i < (int)solution.size(); i++)
        out << i << " " << solution[i] << endl;
}

static void runIterativeSolvers(Matrix A, Matrix B, int n)
{
    cout << "\nPreparing iterative matrix once...\n";
    Iterative::ensureDiagonallyDominant(A);

    Jacobi jSolver(n, n + 1);
    GaussSeidel gsSolver(n, n + 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            jSolver(i, j) = A(i, j);
            gsSolver(i, j) = A(i, j);
        }
        jSolver(i, n) = B(i, 0);
        gsSolver(i, n) = B(i, 0);
    }

    cout << "\nSolving using Jacobi...\n";
    saveVectorSolution("solution_jacobi.dat", jSolver.solveIterative());

    cout << "Solving using Gauss-Seidel...\n";
    saveVectorSolution("solution_gs.dat", gsSolver.solveIterative());

    cout << "\nIterative solutions saved to solution_jacobi.dat and solution_gs.dat\n";
}

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

        vector<fs::path> files = listTextFiles("Large_Matrix");
        if (files.empty())
            throw runtime_error("No .txt input files found in Large_Matrix/");

        vector<fs::path> leftFiles = filterFilesForShape(files, n, n, false);
        vector<fs::path> rightFiles = filterFilesForShape(files, n, m, true);

        if (leftFiles.empty() || rightFiles.empty())
            throw runtime_error("No compatible input files found for the chosen size. Check n and m.");

        cout << "\nCompatible LEFT matrix files (" << n << "x" << n << "):\n";
        for (size_t i = 0; i < leftFiles.size(); ++i)
            cout << "  " << (i + 1) << ". " << leftFiles[i].filename().string() << endl;

        cout << "\nCompatible RIGHT matrix files (" << n << "x" << m << "):\n";
        for (size_t i = 0; i < rightFiles.size(); ++i)
            cout << "  " << (i + 1) << ". " << rightFiles[i].filename().string() << endl;

        int leftIndex = chooseFileIndex(leftFiles, "\nChoose the LEFT matrix file (A):");
        int rightIndex = chooseFileIndex(rightFiles, "\nChoose the RIGHT matrix file (B):");

        Matrix A = loadMatrixFlexible(leftFiles[leftIndex], n, n);
        Matrix B = loadMatrixFlexible(rightFiles[rightIndex], n, m);

        cout << "\nChecking matrix properties...";
        A.displayProperties();

        SLE Aug(n, n + m);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Aug(i, j) = A(i, j);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Aug(i, n + j) = B(i, j);

        int choice;
        vector<long double> solution;

        cout << "\n========== SELECT SOLVING METHOD ==========\n";
        cout << "1. Gaussian Elimination\n";
        cout << "2. LU Decomposition\n";
        cout << "   2.1. Doolittle Method\n";
        cout << "   2.2. Crout Method\n";
        cout << "   2.3. Cholesky Method\n";
        cout << "3. Iterative Methods\n";
        cout << "   3.1. Jacobi\n";
        cout << "   3.2. Gauss-Seidel\n";
        cout << "==========================================\n";
        cout << "Enter your choice (1, 2, or 3): ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nSolving using Gaussian Elimination...\n";
            solution = Aug.solve(SLE::GAUSSIAN);
        }
        else if (choice == 2)
        {
            int lu_choice;
            cout << "\nSelect LU Decomposition Method:\n";
            cout << "1. Doolittle\n";
            cout << "2. Crout\n";
            cout << "3. Cholesky\n";
            cout << "Enter your choice (1-3): ";
            cin >> lu_choice;

            SLE::LUMethod lu_method;
            string method_name;

            switch (lu_choice)
            {
            case 1:
                lu_method = SLE::DOOLITTLE;
                method_name = "Doolittle";
                break;
            case 2:
                lu_method = SLE::CROUT;
                method_name = "Crout";
                break;
            case 3:
                lu_method = SLE::CHOLESKY;
                method_name = "Cholesky";
                break;
            default:
                cout << "Invalid choice! Using Doolittle...\n";
                lu_method = SLE::DOOLITTLE;
                method_name = "Doolittle";
            }

            cout << "\nSolving using LU Decomposition (" << method_name << ")...\n";
            solution = Aug.solve(SLE::LU_METHOD, lu_method);
        }
        else if (choice == 3)
        {
            int iterative_choice;
            cout << "\nSelect Iterative Method:\n";
            cout << "1. Jacobi\n";
            cout << "2. Gauss-Seidel\n";
            cout << "Enter your choice (1-2): ";
            cin >> iterative_choice;

            if (iterative_choice != 1 && iterative_choice != 2)
                cout << "Invalid choice! Using both iterative methods...\n";

            runIterativeSolvers(A, B, n);
            return 0;
        }
        else
        {
            cout << "Invalid choice! Using Gaussian Elimination...\n";
            cout << "\nSolving using Gaussian Elimination...\n";
            solution = Aug.solve(SLE::GAUSSIAN);
        }

        cout << "Solved successfully.\n";

        saveVectorSolution("solution.dat", solution);

        cout << "Solution saved to solution.dat\n";

        if (system("gnuplot --version > /dev/null 2>&1") == 0)
            system("gnuplot plot.gnu_graph");
        else
            cout << "gnuplot is not installed, so the plot step was skipped.\n";
    }
    catch (const exception &e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
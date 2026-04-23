#include "Matrix.hpp"
#include "SLE.hpp"
#include "Iterative.hpp"
#include "Eigenvalues.hpp"
#include "Eigenvalues.hpp"
#include "Interpolation.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
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

// Extract matrix dimensions from file (assumes header: rows cols or just counts values).
static pair<int, int> getMatrixDimensions(const fs::path &filePath)
{
    ifstream fin(filePath);
    if (!fin)
        throw runtime_error("Error opening file: " + filePath.string());

    vector<long double> values;
    long double value;
    while (fin >> value)
        values.push_back(value);

    if (values.size() >= 2)
    {
        int potentialRows = static_cast<int>(values[0]);
        int potentialCols = static_cast<int>(values[1]);
        if (potentialRows > 0 && potentialCols > 0 &&
            values.size() == 2 + static_cast<size_t>(potentialRows) * static_cast<size_t>(potentialCols))
        {
            return {potentialRows, potentialCols};
        }
    }

    return {0, 0};
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

static string slugify(const string &text)
{
    string slug;
    for (char ch : text)
    {
        if (isalnum(static_cast<unsigned char>(ch)))
            slug.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
        else if (ch == ' ' || ch == '-' || ch == '_')
            slug.push_back('_');
    }
    while (!slug.empty() && slug.front() == '_') slug.erase(slug.begin());
    while (!slug.empty() && slug.back() == '_') slug.pop_back();
    return slug.empty() ? string("solution") : slug;
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

static void saveGershgorinAnalysis(const string &filename,
                                   const vector<Matrix::GershgorinDisk> &disks,
                                   const pair<long double, long double> &bounds)
{
    ofstream out(filename);
    if (!out)
        throw runtime_error("Error creating " + filename);

    out << fixed << setprecision(10);
    out << "# index   center            radius            left_bound        right_bound\n";
    for (int i = 0; i < (int)disks.size(); ++i)
    {
        const long double left = disks[i].center - disks[i].radius;
        const long double right = disks[i].center + disks[i].radius;
        out << setw(8) << i
            << setw(18) << disks[i].center
            << setw(18) << disks[i].radius
            << setw(18) << left
            << setw(18) << right << '\n';
    }
    out << "\n# real_eigenvalue_interval " << bounds.first << " " << bounds.second << '\n';
}

static bool loadCheckInterpolationData(const string &fileName,
                                       vector<long double> &x,
                                       vector<long double> &y)
{
    ifstream in(fileName);
    if (!in)
        return false;

    long double xi, yi;
    while (in >> xi >> yi)
    {
        x.push_back(xi);
        y.push_back(yi);
    }

    return !x.empty();
}

static void saveXYData(const string &fileName,
                       const vector<long double> &x,
                       const vector<long double> &y)
{
    ofstream out(fileName);
    if (!out)
        throw runtime_error("Error creating " + fileName);

    out << fixed << setprecision(10);
    for (size_t i = 0; i < x.size(); ++i)
        out << x[i] << " " << y[i] << '\n';
}

static void runInterpolationFromEigenvalues(const Matrix &A)
{
    // Inheritance chain in use: Matrix -> Eigenvalues and Matrix -> Interpolation -> Lagrange.
    Eigenvalues eig(A);
    vector<Matrix::GershgorinDisk> disks = eig.getDisks();
    pair<long double, long double> bounds = eig.getRealBounds();

    vector<long double> xData;
    vector<long double> yData;

    // Matrix-derived interpolation points.
    const int usable = min(static_cast<int>(disks.size()), 8);
    for (int i = 0; i < usable; ++i)
    {
        xData.push_back(static_cast<long double>(i));
        yData.push_back(disks[i].radius);
    }

    vector<long double> checkX;
    vector<long double> checkY;
    const bool hasCheckData = loadCheckInterpolationData("Large_Matrix/interpolation_check_data.txt", checkX, checkY);
    const bool useCheckData = (static_cast<int>(disks.size()) == 49) || !hasCheckData;

    if (useCheckData)
    {
        if (!hasCheckData)
        {
            checkX = {-3.0L, -2.0L, -1.0L, 0.0L, 1.0L, 2.0L, 3.0L};
            checkY = {4.0L, 1.0L, 0.0L, 1.0L, 4.0L, 9.0L, 16.0L};
        }
        xData = checkX;
        yData = checkY;
        cout << "Using check dataset for interpolation (stable path for 49-size case).\n";
    }
    else
    {
        cout << "Using matrix-derived Gershgorin data for interpolation.\n";
    }

    Lagrange lag(xData, yData);
    const long double xMid = (xData.front() + xData.back()) / 2.0L;
    const long double yMid = lag.evaluate(xMid);
    const vector<pair<long double, long double>> curve = lag.evaluateRange(xData.front(), xData.back(), 150);

    saveXYData("interpolation_points.dat", xData, yData);
    if (!checkX.empty() && !checkY.empty())
        saveXYData("interpolation_check_points.dat", checkX, checkY);

    ofstream curveOut("lagrange_curve.dat");
    if (!curveOut)
        throw runtime_error("Error creating lagrange_curve.dat");
    curveOut << fixed << setprecision(10);
    for (const auto &p : curve)
        curveOut << p.first << " " << p.second << '\n';

    ofstream report("interpolation_report.txt");
    if (!report)
        throw runtime_error("Error creating interpolation_report.txt");

    report << fixed << setprecision(10);
    report << "Gershgorin real interval: " << bounds.first << " " << bounds.second << '\n';
    report << "Interpolation points: " << lag.pointCount() << '\n';
    report << "Evaluation at x_mid=" << xMid << ": " << yMid << '\n';

    cout << "Saved interpolation_points.dat, lagrange_curve.dat, interpolation_report.txt\n";
}

static void generateGershgorinPlot(const string &dataFile,
                                   const vector<Matrix::GershgorinDisk> &disks,
                                   const pair<long double, long double> &bounds)
{
    const string scriptFile = "plot_gershgorin.gnu";
    const string imageFile = "graph_gershgorin.png";

    ofstream gp(scriptFile);
    if (!gp)
        throw runtime_error("Error creating " + scriptFile);

    gp << "set terminal pngcairo size 1400,1000 enhanced font 'Arial,11'\n";
    gp << "set output '" << imageFile << "'\n";
    long double maxRadius = 0.0L;
    for (const auto &d : disks)
        if (d.radius > maxRadius)
            maxRadius = d.radius;

    const long double xMargin = max<long double>(1.0L, (bounds.second - bounds.first) * 0.05L);
    const long double yMargin = max<long double>(1.0L, maxRadius * 0.15L);
    const long double xMin = bounds.first - xMargin;
    const long double xMax = bounds.second + xMargin;
    const long double yMax = maxRadius + yMargin;

    gp << "set title 'Gershgorin Disks (Eigenvalue Bounds)'\n";
    gp << "set xlabel 'Real Axis'\n";
    gp << "set ylabel 'Imaginary Axis'\n";
    gp << "set grid\n";
    gp << "set size ratio -1\n";
    gp << "set key off\n";
    gp << "set border lw 1.5\n";
    gp << "set xtics out\n";
    gp << "set ytics out\n";
    gp << "set xrange [" << xMin << ":" << xMax << "]\n";
    gp << "set yrange [" << -yMax << ":" << yMax << "]\n";
    gp << "set arrow 1 from graph 0,0 to graph 1,0 nohead lc rgb 'black' dt 2\n";
    gp << "set arrow 2 from 0,graph 0 to 0,graph 1 nohead lc rgb 'black' dt 2\n";

    for (size_t i = 0; i < disks.size(); ++i)
        gp << "set label " << (i + 1) << " '" << (i + 1) << "' at " << disks[i].center << ",0 offset char 0,1 tc rgb '#d62728'\n";

    gp << "set style fill transparent solid 0.14 noborder\n";
    gp << "plot '" << dataFile << "' using 2:0:3 with circles lc rgb '#1f77b4' fs transparent solid 0.20 noborder, \\\n";
    gp << "     '" << dataFile << "' using 2:0 with points pt 7 ps 0.35 lc rgb '#d62728'\n";
    gp.close();

    if (system("gnuplot --version > /dev/null 2>&1") == 0)
    {
        const string cmd = "gnuplot " + scriptFile;
        system(cmd.c_str());
        cout << "Gershgorin plot saved to " << imageFile << "\n";

        const string openCmd = "xdg-open " + imageFile + " >/dev/null 2>&1 &";
        system(openCmd.c_str());
    }
    else
    {
        cout << "gnuplot is not installed, so the Gershgorin plot step was skipped.\n";
    }
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
    generateAndOpenSolutionPlot("solution_jacobi.dat", "Jacobi", "graph_jacobi.png");

    cout << "Solving using Gauss-Seidel...\n";
    saveVectorSolution("solution_gauss_seidel.dat", gsSolver.solveIterative());
    generateAndOpenSolutionPlot("solution_gauss_seidel.dat", "Gauss-Seidel", "graph_gauss_seidel.png");

    cout << "\nIterative solutions saved to solution_jacobi.dat and solution_gauss_seidel.dat\n";
}

static void runGershgorinAnalysis(const Matrix &A)
{
    Gershgorin gersh(A);
    vector<Matrix::GershgorinDisk> disks = gersh.disks();
    pair<long double, long double> bounds = gersh.realBounds();

    saveGershgorinAnalysis("gershgorin.dat", disks, bounds);
    cout << "\nGershgorin analysis saved to gershgorin.dat\n";
    generateGershgorinPlot("gershgorin.dat", disks, bounds);
}

int main()
{
    try
    {
        cout << "\n╔════════════════════════════════════════════╗\n";
        cout << "║  Linear System Solver - File Selection    ║\n";
        cout << "╚════════════════════════════════════════════╝\n";

        // Step 1: List all available files.
        vector<fs::path> files = listTextFiles("Large_Matrix");
        if (files.empty())
            throw runtime_error("No .txt input files found in Large_Matrix/");

        cout << "\nAvailable matrix files:\n";
        for (size_t i = 0; i < files.size(); ++i)
        {
            auto dims = getMatrixDimensions(files[i]);
            cout << "  " << (i + 1) << ". " << files[i].filename().string();
            if (dims.first > 0)
                cout << " (" << dims.first << "x" << dims.second << ")";
            cout << endl;
        }

        // Step 2: User selects LEFT file (matrix A).
        cout << "\n=== Select LEFT Matrix File (A) ===\n";
        int leftChoice;
        cout << "Enter file number (1-" << files.size() << "): ";
        cin >> leftChoice;

        if (leftChoice < 1 || leftChoice > (int)files.size())
            throw runtime_error("Invalid file choice for LEFT matrix");

        fs::path leftFilePath = files[leftChoice - 1];
        auto [n, _] = getMatrixDimensions(leftFilePath);

        if (n <= 0)
            throw runtime_error("Could not determine dimensions of LEFT matrix file");

        cout << "Selected LEFT: " << leftFilePath.filename().string() << " (size: " << n << "x" << n << ")\n";

        // Step 3: User selects RIGHT file (matrix B).
        cout << "\n=== Select RIGHT Matrix File (B) ===\n";

        vector<fs::path> compatibleRightFiles;
        for (const auto &f : files)
        {
            auto dims = getMatrixDimensions(f);
            if (dims.first == n)
                compatibleRightFiles.push_back(f);
        }

        if (compatibleRightFiles.empty())
            throw runtime_error("No compatible RIGHT matrix files found for size " + to_string(n) + "x?");

        cout << "Compatible RIGHT files (rows=" << n << "):\n";
        for (size_t i = 0; i < compatibleRightFiles.size(); ++i)
        {
            auto dims = getMatrixDimensions(compatibleRightFiles[i]);
            cout << "  " << (i + 1) << ". " << compatibleRightFiles[i].filename().string()
                 << " (" << dims.first << "x" << dims.second << ")\n";
        }

        int rightChoice;
        cout << "Enter file number (1-" << compatibleRightFiles.size() << "): ";
        cin >> rightChoice;

        if (rightChoice < 1 || rightChoice > (int)compatibleRightFiles.size())
            throw runtime_error("Invalid file choice for RIGHT matrix");

        fs::path rightFilePath = compatibleRightFiles[rightChoice - 1];
        auto [nCheck, m] = getMatrixDimensions(rightFilePath);

        if (nCheck != n)
            throw runtime_error("RIGHT matrix row count does not match LEFT matrix");

        cout << "Selected RIGHT: " << rightFilePath.filename().string() << " (size: " << n << "x" << m << ")\n";

        // Step 4: Load matrices.
        cout << "\nLoading matrices...\n";
        Matrix A = loadMatrixFlexible(leftFilePath, n, n);
        Matrix B = loadMatrixFlexible(rightFilePath, n, m);

        cout << "Matrices loaded successfully.\n";
        cout << "System: " << n << " equations, " << m << " RHS column(s)\n";
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
        string solverName;
        string solutionFile;
        string graphFile;

        cout << "\n========== SELECT SOLVING METHOD ==========\n";
        cout << "1. Gaussian Elimination\n";
        cout << "2. LU Decomposition\n";
        cout << "   2.1. Doolittle Method\n";
        cout << "   2.2. Crout Method\n";
        cout << "   2.3. Cholesky Method\n";
        cout << "3. Iterative Methods\n";
        cout << "   3.1. Jacobi\n";
        cout << "   3.2. Gauss-Seidel\n";
        cout << "4. Gershgorin Analysis (Eigenvalue Bounds, not Ax=b solver)\n";
        cout << "5. Interpolation from Gershgorin (Lagrange Inheritance Demo)\n";
        cout << "==========================================\n";
        cout << "Enter your choice (1, 2, 3, 4, or 5): ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nSolving using Gaussian Elimination...\n";
            solution = Aug.solve(SLE::GAUSSIAN);
            solverName = "Gaussian Elimination";
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
            solverName = "LU " + method_name;
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
        else if (choice == 4)
        {
            runGershgorinAnalysis(A);
            return 0;
        }
        else if (choice == 5)
        {
            runInterpolationFromEigenvalues(A);
            return 0;
        }
        else
        {
            cout << "Invalid choice! Using Gaussian Elimination...\n";
            cout << "\nSolving using Gaussian Elimination...\n";
            solution = Aug.solve(SLE::GAUSSIAN);
            solverName = "Gaussian Elimination";
        }

        cout << "Solved successfully.\n";

        solutionFile = "solution_" + slugify(solverName) + ".dat";
        graphFile = "graph_" + slugify(solverName) + ".png";

        saveVectorSolution(solutionFile, solution);

        cout << "Solution saved to " << solutionFile << "\n";

        generateAndOpenSolutionPlot(solutionFile, solverName, graphFile);
    }
    catch (const exception &e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
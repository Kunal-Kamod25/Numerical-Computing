#include "Eigenvalues.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

Eigenvalues::Eigenvalues() : Matrix() {}
Eigenvalues::Eigenvalues(int r, int c) : Matrix(r, c) {}
Eigenvalues::Eigenvalues(const Matrix &base) : Matrix(base) {}
vector<Matrix::GershgorinDisk> Eigenvalues::getDisks() const
{
    if (!isSquare())
        throw runtime_error("Gershgorin analysis requires a square matrix.");

    vector<Matrix::GershgorinDisk> disks(rows);
    for (int i = 0; i < rows; ++i)
    {
        long double radius = 0.0L;
        for (int j = 0; j < cols; ++j)
        {
            if (i != j)
                radius += fabsl(mat[i][j]);
        }
        disks[i] = {mat[i][i], radius};
    }

    return disks;
}

pair<long double, long double> Eigenvalues::getRealBounds() const
{
    const vector<Matrix::GershgorinDisk> disks = getDisks();

    long double minBound = disks[0].center - disks[0].radius;
    long double maxBound = disks[0].center + disks[0].radius;

    for (const auto &disk : disks)
    {
        minBound = min(minBound, disk.center - disk.radius);
        maxBound = max(maxBound, disk.center + disk.radius);
    }

    return {minBound, maxBound};
}

Gershgorin::Gershgorin() : Eigenvalues() {}

Gershgorin::Gershgorin(int r, int c) : Eigenvalues(r, c) {}

Gershgorin::Gershgorin(const Matrix &base) : Eigenvalues(base) {}

vector<Matrix::GershgorinDisk> Gershgorin::disks() const
{
    return getDisks();
}

pair<long double, long double> Gershgorin::realBounds() const
{
    return getRealBounds();
}

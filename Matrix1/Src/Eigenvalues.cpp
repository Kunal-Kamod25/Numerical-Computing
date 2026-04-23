#include "Eigenvalues.hpp"
#include "Gershgorin.hpp"

using namespace std;

Eigenvalues::Eigenvalues() : Matrix() {}

Eigenvalues::Eigenvalues(int r, int c) : Matrix(r, c) {}

Eigenvalues::Eigenvalues(const Matrix &base) : Matrix(base) {}

vector<Matrix::GershgorinDisk> Eigenvalues::getDisks() const
{
    return gershgorinDisks();
}

pair<long double, long double> Eigenvalues::getRealBounds() const
{
    return gershgorinRealBounds();
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

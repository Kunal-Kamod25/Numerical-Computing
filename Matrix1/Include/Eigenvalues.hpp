#ifndef EIGENVALUES_HPP
#define EIGENVALUES_HPP

#include "Matrix.hpp"
#include <utility>
#include <vector>

// Matrix-specialized class for Gershgorin-based eigenvalue bounds.
class Eigenvalues : public Matrix
{
public:
    Eigenvalues();
    Eigenvalues(int r, int c);
    Eigenvalues(const Matrix &base);

    std::vector<GershgorinDisk> getDisks() const;
    std::pair<long double, long double> getRealBounds() const;
};

// Gershgorin analysis class inheriting from Eigenvalues.
// No extra data members are introduced; it uses inherited Matrix storage.
class Gershgorin : public Eigenvalues
{
public:
    Gershgorin();
    Gershgorin(int r, int c);
    Gershgorin(const Matrix &base);

    std::vector<Matrix::GershgorinDisk> disks() const;
    std::pair<long double, long double> realBounds() const;
};

#endif

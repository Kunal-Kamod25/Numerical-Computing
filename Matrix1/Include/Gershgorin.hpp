#ifndef GERSHGORIN_HPP
#define GERSHGORIN_HPP

#include "Eigenvalues.hpp"
#include <utility>
#include <vector>

// Gershgorin analysis class explicitly inheriting from Eigenvalues.
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

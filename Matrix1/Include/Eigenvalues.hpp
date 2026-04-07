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

#endif

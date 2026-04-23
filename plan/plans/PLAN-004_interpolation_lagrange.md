# PLAN-004: Interpolation (Lagrange Method)

**Created:** 2026-04-19
**Status:** Draft
**Addresses:** Porting the `Interpolation` base class and `Lagrange` solver from `Matrix1` to `Matrixpy`.

---

## 1. Context & motivation

Interpolation is used to estimate values between discrete data points. The C++ library implements this via an abstract `Interpolation` base class and a concrete `Lagrange` subclass. This plan ports these components to the Python environment while maintaining the inheritance from the `Matrix` class.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/interpolation.py` (Abstract `Interpolation` class and concrete `Lagrange` class)
- **Src Layer**:
    - `Matrixpy/Src/Interpolation.py` (Core mathematical logic for Lagrange polynomials)
- **Main Layer**:
    - `Matrixpy/Main/main_interpolation.py` (Functional mirror of `Main_Interpolation.cpp`)

## 3. Approach

- **Inheritance Chain**:
    - `Matrix` → `Interpolation` → `Lagrange`
- **Algorithm**:
    - **Lagrange Basis**: $L_i(x) = \prod_{j=0, j \neq i}^n \frac{x - x_j}{x_i - x_j}$
    - **Polynomial**: $P(x) = \sum_{i=0}^n y_i L_i(x)$
- **Mirroring**:
    - Use `Matrix` storage (n x 2) to hold $(x, y)$ pairs as per the C++ implementation.
    - Implement `evaluateRange()` for generating curve data points.

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Include/interpolation.py` with class hierarchy | 20 min | PLAN-003 |
| 2 | Create `Src/Interpolation.py` with Lagrange evaluation logic | 30 min | 1 |
| 3 | Implement `Main/main_interpolation.py` with evaluation and file IO | 25 min | 2 |
| 4 | Verification with test data points | 15 min | 3 |

## 5. Success criteria

- `main_interpolation.py` correctly calculates values for intermediate points.
- The output matches the behavior of the C++ `evaluateRange()` (generating a list of points).
- Mathematical parity: $P(x_i) = y_i$ for all input points.

## 6. References

- `Matrix1/Include/Interpolation.hpp`
- `Matrix1/Src/Interpolation.cpp`
- `Matrix1/Main_Interpolation.cpp`

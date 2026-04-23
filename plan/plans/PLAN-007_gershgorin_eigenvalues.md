# PLAN-007: Gershgorin Eigenvalues (Mirroring Eigenvalues.hpp & Gershgorin.hpp)

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Porting the `Eigenvalues` and `Gershgorin` classes for spectral analysis of matrices.

---

## 1. Context & motivation

The C++ library uses Gershgorin's Circle Theorem to estimate the bounds of eigenvalues for a given matrix. This is implemented via two specialized classes, `Eigenvalues` and `Gershgorin`, which inherit from `Matrix`. This plan ports these classes to `Matrixpy`.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/eigenvalues.py` (Mirroring `Eigenvalues.hpp`)
    - `Matrixpy/Include/gershgorin.py` (Mirroring `Gershgorin.hpp`)
- **Src Layer**:
    - `Matrixpy/Src/Eigenvalues.py` (Mirroring `Eigenvalues.cpp`)
    - Update `Matrixpy/Src/Matrix_Algorithms.py` with `get_gershgorin_real_bounds`.
- **Main Layer**:
    - `Matrixpy/Main/main_gershgorin.py` (Demo for Gershgorin analysis)

## 3. Approach

- **Inheritance Chain**:
    - `Matrix` → `Eigenvalues` → `Gershgorin`
- **Algorithm Distribution**:
    - Core logic (`get_gershgorin_disks` and `get_gershgorin_real_bounds`) resides in `Matrixpy/Src/Matrix_Algorithms.py`.
    - The `Eigenvalues` and `Gershgorin` classes provide convenient wrappers for these algorithms.

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Implement `get_gershgorin_real_bounds` in `Src/Matrix_Algorithms.py` | 10 min | PLAN-003 |
| 2 | Create `Include/eigenvalues.py` and `Include/gershgorin.py` | 20 min | 1 |
| 3 | Create `Src/Eigenvalues.py` implementing the logic for both classes | 20 min | 2 |
| 4 | Create `Main/main_gershgorin.py` for verification | 15 min | 3 |

## 5. Success criteria

- `main_gershgorin.py` correctly calculates Gershgorin disks and real eigenvalue bounds.
- The inheritance structure matches the C++ project.
- Verification: For a simple diagonal matrix, the disks should be centered at the diagonal elements with radius 0.

## 6. References

- `Matrix1/Include/Eigenvalues.hpp`
- `Matrix1/Include/Gershgorin.hpp`
- `Matrix1/Src/Eigenvalues.cpp`
- `Matrix1/Src/Matrix_Algorithms.cpp`

# PLAN-005: SLE & Gaussian Elimination (Mirroring SLE.hpp & Matrix_Algorithms.cpp) [REVISED]

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Porting `SLE` and `GaussianElimination` to follow the C++ file-for-file mirror.

---

## 1. Context & motivation

In the C++ library, the methods for `GaussianElimination` and `SLE` are implemented within `Matrix_Algorithms.cpp`. This revised plan ensures that our Python implementation follows this structure by adding these methods to `Matrixpy/Src/Matrix_Algorithms.py`.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/gauss_elimination.py` (Mirroring `gauss_elimination.hpp`)
    - `Matrixpy/Include/sle.py` (Mirroring `SLE.hpp`)
- **Src Layer**:
    - `Matrixpy/Src/Matrix_Algorithms.py` (Extended with `GaussianElimination` and `SLE` methods)
- **Main Layer**:
    - `Matrixpy/Main/main_sle.py`

## 3. Approach

- **`Matrixpy/Src/Matrix_Algorithms.py`**:
    - This file will now house:
        - `Matrix` algorithms (determinant, inverse, gershgorin).
        - `GaussianElimination` methods (pivoting, triangular form).
        - `SLE` methods (back substitution, solve).
- **Imports**: The classes in `Include/` will import their respective logic from `Src/Matrix_Algorithms.py`.

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Port `gauss_elimination.py` and `sle.py` declarations to `Include/` | 20 min | PLAN-003 |
| 2 | Port `GaussianElimination` and `SLE` logic to `Matrixpy/Src/Matrix_Algorithms.py` | 40 min | 1 |
| 3 | Create `Matrixpy/Main/main_sle.py` demo | 15 min | 2 |

## 5. Success criteria

- `GaussianElimination` and `SLE` methods are centralized in `Matrix_Algorithms.py`.
- `main_sle.py` works correctly with the consolidated algorithm file.

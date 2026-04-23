# PLAN-003: Matrixpy Core Port (Mirroring Matrix.hpp & Matrix_Methods.cpp) [REVISED]

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Porting core `Matrix` functionality into a strict file-for-file mirror of the C++ structure.

---

## 1. Context & motivation

The user requested a closer mirror of the C++ file organization. In the original project, `Matrix.hpp` methods are split across `Matrix_Methods.cpp` and `Matrix_Algorithms.cpp`. This revised plan ensures that the Python port follows this exact naming and logic distribution.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/matrix.py` (Mirroring `Matrix.hpp`)
- **Src Layer (Algorithm Files)**:
    - `Matrixpy/Src/Matrix_Methods.py` (Mirroring `Matrix_Methods.cpp`)
    - `Matrixpy/Src/Matrix_Algorithms.py` (Mirroring the `Matrix` methods in `Matrix_Algorithms.cpp`)
- **Main Layer**:
    - `Matrixpy/Main/main_matrix.py`

## 3. Approach

- **`Matrixpy/Include/matrix.py`**:
    - Contains `BaseMatrix` and `Matrix` class definitions.
    - Methods will import their logic from either `Matrix_Methods` or `Matrix_Algorithms` depending on where they reside in C++.
- **`Matrixpy/Src/Matrix_Methods.py`**:
    - Contains basic operators (+, -, *, /) and property checks (isSquare, isSymmetric, etc.).
- **`Matrixpy/Src/Matrix_Algorithms.py`**:
    - Contains advanced algorithms for the `Matrix` class (determinant, inverse, gershgorinDisks).

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Matrixpy` directory structure | 5 min | — |
| 2 | Implement `Matrixpy/Include/matrix.py` | 20 min | 1 |
| 3 | Implement `Matrixpy/Src/Matrix_Methods.py` | 30 min | 2 |
| 4 | Implement `Matrixpy/Src/Matrix_Algorithms.py` (Part 1: Matrix methods) | 30 min | 2 |
| 5 | Create `Matrixpy/Main/main_matrix.py` | 15 min | 3, 4 |

## 5. Success criteria

- File names in `Matrixpy/Src` match the C++ `.cpp` files.
- `main_matrix.py` runs correctly with the new structure.

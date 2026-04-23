# PLAN-008: Iterative Methods (Jacobi & Gauss-Seidel)

**Created:** 2026-04-20
**Status:** Draft
**Addresses:** Porting iterative solvers (Jacobi and Gauss-Seidel) from `Matrix1` to `Matrixpy`.

---

## 1. Context & motivation

Iterative methods solve linear systems by starting with an initial guess and refining it repeatedly until convergence. These methods are particularly useful for large, sparse, diagonally dominant matrices where direct methods (like LU or Gaussian Elimination) might be less efficient. This plan ports the `Iterative`, `Jacobi`, and `GaussSeidel` classes.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/iterative.py` (Base `Iterative` class and derived `Jacobi`, `GaussSeidel` classes)
- **Src Layer**:
    - `Matrixpy/Src/Iterative.py` (Implementation of Jacobi and Gauss-Seidel iterations)
- **Main Layer**:
    - `Matrixpy/Main/main_iterative.py` (Demo for iterative solvers)

## 3. Approach

- **Inheritance Chain**:
    - `SLE` → `Iterative` → `Jacobi` / `GaussSeidel`
- **Algorithms**:
    - **Jacobi**: Updates all values simultaneously using values from the *previous* iteration.
    - **Gauss-Seidel**: Updates values sequentially, using the *latest* available values from the current iteration.
- **Convergence**:
    - Controlled by `max_iterations` and `tolerance`.
    - Requires diagonal dominance for guaranteed convergence.

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Include/iterative.py` with the class hierarchy | 20 min | PLAN-005 |
| 2 | Create `Src/Iterative.py` implementing `Jacobi.solveIterative()` | 30 min | 1 |
| 3 | Implement `GaussSeidel.solveIterative()` in `Src/Iterative.py` | 20 min | 2 |
| 4 | Create `Main/main_iterative.py` for verification | 15 min | 3 |

## 5. Success criteria

- `main_iterative.py` successfully solves a diagonally dominant 3x3 system.
- Jacobi and Gauss-Seidel converge within a reasonable number of iterations.
- Gauss-Seidel should typically converge faster than Jacobi.

## 6. References

- `Matrix1/Include/Iterative.hpp`
- `Matrix1/Src/Iterative.cpp`

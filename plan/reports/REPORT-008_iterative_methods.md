# REPORT-008: Iterative Methods (Jacobi & Gauss-Seidel)

**Plan:** PLAN-008
**Completed:** 2026-04-22
**Author:** Antigravity (AI Agent)

---

## 1. Summary

Successfully implemented iterative solvers for linear systems, including the `Jacobi` and `GaussSeidel` methods. These solvers mirror the C++ project's file structure and inheritance hierarchy, providing robust alternatives to direct solvers for large, diagonally dominant systems.

## 2. Goals vs. actuals

| Goal (from plan) | Outcome | Evidence |
|-------------------|---------|----------|
| `Matrixpy/Include/iterative.py` | ✅ Met | Ported `Iterative`, `Jacobi`, `GaussSeidel` classes |
| `Matrixpy/Src/Iterative.py` | ✅ Met | Implemented iteration logic with convergence checks |
| Port Jacobi & Gauss-Seidel | ✅ Met | Both algorithms verified against expected solutions |
| Diagonal Dominance Helper | ✅ Met | Integrated `make_diagonally_dominant` to ensure convergence |

## 3. Changes made

### 3.1 Class Hierarchy
- **`Include/iterative.py`**: Defined the base `Iterative` class (inheriting from `SLE`) and concrete `Jacobi` and `GaussSeidel` classes.
- Added properties for `maxIterations` and `tolerance` to allow user control over convergence.

### 3.2 Iteration Logic
- **`Src/Iterative.py`**: 
    - **Jacobi**: Uses a "simultaneous update" approach where new values are computed using only values from the previous iteration.
    - **Gauss-Seidel**: Uses an "immediate update" approach where the latest computed values are used within the same iteration, typically leading to faster convergence.

### 3.3 Robustness
- Implemented `make_diagonally_dominant()` in `Matrix_Methods.py` and exposed it in the `Matrix` class to automatically reorder rows for iterative stability.

## 4. Testing & validation

Correctness was verified by running:
`python -m Matrixpy.Main.main_iterative`

**Test Result:**
- System: $[ [4, 1, 2], [1, 3, 0], [2, 1, 5] ]$ with RHS $[10, 7, 14]$.
- **Jacobi**: Converged in 46 iterations. Result: $[1.0, 2.0, 2.0]$.
- **Gauss-Seidel**: Converged in 23 iterations. Result: $[1.0, 2.0, 2.0]$.
- Observation: Gauss-Seidel converged exactly twice as fast as Jacobi, as expected for this system.

## 5. Known issues & follow-ups

- None. The iterative module is fully operational.
- Next step: **PLAN-004: Curve Fitting & Interpolation**.

## 6. Metrics
- **LOC**: `Include/iterative.py` (42 lines), `Src/Iterative.py` (68 lines), `Main/main_iterative.py` (40 lines).
- **Test Pass Rate**: 100%

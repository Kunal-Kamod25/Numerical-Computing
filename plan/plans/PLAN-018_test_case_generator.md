# PLAN-018: Test Case Generation Utility

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** The need for a centralized script to generate mathematically significant test data (ill-conditioned, diagonally dominant, noisy) for validation.

---

## 1. Context & motivation
While we have a collection of static test files, a dynamic generation utility allows us to create larger systems (e.g., 10x10 or 20x20) and specialized matrices (like Hilbert matrices) that are difficult to write manually. This will ensure the library handles "tough" numerical problems correctly.

## 2. Goals
- Create `Matrixpy/Src/Data_Generator.py`.
- Implement specialized generators for **all library modules**:
    1. **Matrix**: Symmetric, Identity, and Singular matrix generators.
    2. **SLE & LU**: Random systems and specific LU-factorable matrices.
    3. **Iterative**: Guaranteed Diagonally Dominant matrices ($|a_{ii}| > \sum |a_{ij}|$).
    4. **Interpolation**: Clean polynomial datasets (quadratic, cubic) for exact reconstruction testing.
    5. **Curve Fitting**: Synthetic linear data with customizable Gaussian noise.
- Ensure automated file saving into the respective `Matrixpy/Inputs/` subdirectories.

## 3. Non-goals
- Generating non-square matrices for solvers (the library focus is on square SLE).
- Complex number matrix generation (this remains a future task).

## 4. Approach
The utility will be a standalone Python script using the standard `random` library. It will provide a command-line interface or simple function calls to save generated data directly into the `Matrixpy/Inputs/` folder.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Matrixpy/Src/Data_Generator.py` base utility | 10 min | — |
| 2 | Implement Matrix & SLE generators (Random, Symmetric, Singular) | 20 min | 1 |
| 3 | Implement LU-specific generators (Perfect Factorization) | 15 min | 1 |
| 4 | Implement Iterative generator (Strict Diagonal Dominance) | 15 min | 1 |
| 5 | Implement Interpolation & Curve Fitting data generators | 20 min | 1 |
| 6 | Create `generate_test_suite.py` CLI for user access | 20 min | 2,3,4,5 |

## 6. Success criteria
- The script successfully creates valid `.txt` files that `Matrixpy` can read.
- The generated diagonally dominant matrices successfully converge in the `Iterative` solver.
- The Hilbert matrix demonstrates the expected loss of precision for $n > 10$.

## 7. References
- `Matrixpy/Src/Matrix_Methods.py` (File I/O logic)
- Numerical Recipes (Hilbert Matrix definition)

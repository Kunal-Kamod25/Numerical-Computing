# PLAN-016: Comprehensive Input File Generation

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** The need for a wider variety of test cases and input files for all numerical methods.

---

## 1. Context & motivation
Currently, the `Matrixpy/Inputs/` subdirectories only contain a single basic test file for each method (e.g., `system_3x3.txt`, `fitting_data.txt`). To fully test and demonstrate the library's capabilities, we need a robust suite of input files covering various mathematical scenarios, including edge cases, optimal conditions, and larger datasets.

## 2. Goals
- Generate diverse test files for **Matrix Analysis** (Symmetric, Singular, Large).
- Generate diverse test files for **SLE / LU / Iterative** (Diagonally Dominant, Non-Convergent, 4x4/5x5 systems).
- Generate diverse test files for **Interpolation** (Polynomial data).
- Generate diverse test files for **Curve Fitting** (Perfect lines, noisy data).

## 3. Non-goals
- Generating massive datasets (e.g., 1000x1000 matrices) that would make the repository too large or slow for simple terminal testing.

## 4. Proposed Files

### Matrix (`Inputs/Matrix/`)
- `matrix_5x5.txt`: A standard 5x5 square matrix.
- `matrix_symmetric.txt`: A perfectly symmetric 4x4 matrix.
- `matrix_singular.txt`: A matrix with a determinant of 0 (for testing error handling).

### SLE / LU / Iterative (`Inputs/SLE/`)
*(Note: Iterative and LU methods share the SLE input format of augmented `[A|B]` matrices)*
- `system_4x4.txt`: A standard 4x4 system with a unique solution.
- `system_diag_dominant.txt`: A 4x4 system strictly diagonally dominant (guaranteed Jacobi convergence).
- `system_singular.txt`: An SLE with no unique solution (to trigger `RuntimeError`).

### Interpolation (`Inputs/Interpolation/`)
- `interp_5pts.txt`: 5 mathematically distinct coordinate points.
- `interp_polynomial.txt`: 10 points sampled perfectly from $y = x^2 - 4x + 3$.

### Curve Fitting (`Inputs/CurveFitting/`)
- `fitting_perfect_line.txt`: 5 points lying exactly on $y = 3x - 2$ (RMS Error should be 0.0).
- `fitting_noisy_data.txt`: 20 points with a strong linear trend but random noise (to show realistic fitting).

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create Matrix property test files | 10 min | — |
| 2 | Create SLE / LU / Iterative test files | 10 min | — |
| 3 | Create Interpolation and Curve Fitting files | 10 min | — |
| 4 | Test loading the new files via `main_master.py` | 5 min | 1, 2, 3 |

## 6. Risks & mitigations
| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Mathematical errors in manual file creation | Low | Med | Use Python scripts internally to pre-calculate and generate the files reliably. |

## 7. Success criteria
- The master menu lists 3-4 distinct files for each numerical method.
- Loading `system_diag_dominant.txt` into Jacobi solves cleanly without requiring row reordering.
- Loading `matrix_singular.txt` returns a determinant of exactly 0.0.

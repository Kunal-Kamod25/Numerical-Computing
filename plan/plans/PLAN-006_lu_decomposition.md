# PLAN-006: LU Decomposition (LU.hpp & LU.cpp Mirror)

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Porting the `LU` decomposition class from `Matrix1` to the `Matrixpy` structure.

---

## 1. Context & motivation

LU Decomposition is an efficient way to solve systems of linear equations, especially when solving multiple systems with the same matrix $A$ but different $B$ vectors. This plan implements the Doolittle, Crout, and Cholesky methods, mirroring the C++ `LU` class.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/lu.py` (Mirroring `LU.hpp`)
- **Src Layer**:
    - `Matrixpy/Src/LU.py` (Mirroring `LU.cpp`)
- **Main Layer**:
    - `Matrixpy/Main/main_lu.py` (Demo for LU solvers)
- **Integration**: Update `SLE.solve()` to support the LU methods.

## 3. Approach

### LU Decomposition Methods
- **Doolittle**: $L$ has 1s on the diagonal. Includes partial pivoting for stability.
- **Crout**: $U$ has 1s on the diagonal. Includes partial pivoting.
- **Cholesky**: $A = LL^T$ (for symmetric positive-definite matrices).

### Solver
- **Forward Substitution**: Solve $Ly = PB$ (where $P$ is the permutation from pivoting).
- **Back Substitution**: Solve $Ux = y$.

### Data Structures
- `L`: Lower triangular matrix.
- `U`: Upper triangular matrix.
- `P`: Permutation vector (list of indices).

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Matrixpy/Include/lu.py` with `LU` class inheriting from `Matrix` | 20 min | PLAN-003 |
| 2 | Create `Matrixpy/Src/LU.py` with Doolittle, Crout, and Cholesky logic | 45 min | 1 |
| 3 | Implement `solve()` method in `Matrixpy/Src/LU.py` (Forward/Back sub) | 30 min | 2 |
| 4 | Implement `Main/main_lu.py` demo | 20 min | 3 |
| 5 | Update `SLE.solve()` in `Src/Matrix_Algorithms.py` to use the `LU` class | 15 min | 4 |

## 5. Success criteria

- `main_lu.py` correctly solves systems using all three LU methods.
- Verification: $L \times U$ should equal the (permuted) original matrix $A$.
- `SLE.solve()` successfully delegates to the `LU` class when the LU method is selected.

## 6. References

- `Matrix1/Include/LU.hpp`
- `Matrix1/Src/LU.cpp`
- `PLAN-005_sle_and_gauss_elimination.md`

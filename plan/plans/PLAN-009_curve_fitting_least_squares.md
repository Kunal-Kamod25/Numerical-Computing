# PLAN-009: Curve Fitting (Least Squares Method)

**Created:** 2026-04-21
**Status:** Draft
**Addresses:** Porting the `CurveFitting` base class and `LeastSquares` solver from `Matrix1` to `Matrixpy`.

---

## 1. Context & motivation

Curve fitting involves finding a mathematical function that best fits a set of data points. The C++ library implements this via an abstract `CurveFitting` base class and a concrete `LeastSquares` subclass for linear regression ($y = ax + b$). This plan ports these components to the Python environment.

## 2. Goals

- **Include Layer**:
    - `Matrixpy/Include/curve_fitting.py` (Abstract `CurveFitting` class and concrete `LeastSquares` class)
- **Src Layer**:
    - `Matrixpy/Src/CurveFitting.py` (Core mathematical logic for solving normal equations)
- **Main Layer**:
    - `Matrixpy/Main/main_curve_fitting.py` (Functional mirror of `Main_CurveFitting.cpp`)

## 3. Approach

- **Inheritance Chain**:
    - `Matrix` → `CurveFitting` → `LeastSquares`
- **Algorithm**:
    - **Normal Equations**:
        1. $a \sum x_i^2 + b \sum x_i = \sum x_i f_i$
        2. $a \sum x_i + b N = \sum f_i$
    - Solve for $a$ (slope) and $b$ (intercept).
    - **RMS Error**: $\sqrt{\frac{\sum (y_i - f_i)^2}{N}}$
- **Mirroring**:
    - Use `Matrix` storage (n x 2) to hold data.
    - Implement `fit()`, `evaluate()`, and `rms()` methods.

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Include/curve_fitting.py` with class hierarchy | 20 min | PLAN-003 |
| 2 | Create `Src/CurveFitting.py` with Least Squares solver logic | 30 min | 1 |
| 3 | Implement `Main/main_curve_fitting.py` demo | 20 min | 2 |
| 4 | Verification with sample datasets | 15 min | 3 |

## 5. Success criteria

- `main_curve_fitting.py` correctly calculates slope and intercept.
- RMS error matches expected values for linear datasets.
- Verification: Fitting points that lie exactly on a line should result in zero RMS error.

## 6. References

- `Matrix1/Include/CurveFitting.hpp`
- `Matrix1/Src/CurveFitting.cpp`
- `Matrix1/Main_CurveFitting.cpp`

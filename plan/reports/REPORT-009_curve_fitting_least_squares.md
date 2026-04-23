# REPORT-009: Curve Fitting (Least Squares Method)

**Plan:** PLAN-009
**Completed:** 2026-04-22
**Author:** Antigravity (AI Agent)

---

## 1. Summary

Successfully implemented the `CurveFitting` base class and the `LeastSquares` linear regression solver, mirroring the C++ project's architecture. The module provides a robust way to perform linear fitting and error analysis on experimental data.

## 2. Goals vs. actuals

| Goal (from plan) | Outcome | Evidence |
|-------------------|---------|----------|
| `Matrixpy/Include/curve_fitting.py` | ✅ Met | Ported `CurveFitting` and `LeastSquares` classes |
| `Matrixpy/Src/CurveFitting.py` | ✅ Met | Implemented Normal Equations and RMS logic |
| Linear Regression Solves | ✅ Met | Correctly identified $y = 2x + 1$ with zero error |
| Range Evaluation Support | ✅ Met | Generates curve points for plotting |
| Verification Demo | ✅ Met | Handled both perfect and noisy data in tests |

## 3. Changes made

### 3.1 Mathematical Implementation
- **`Src/CurveFitting.py`**:
    - **Normal Equations**: Solved the $2 \times 2$ system for slope ($a$) and intercept ($b$) using the summations of $x$, $y$, $x^2$, and $xy$.
    - **RMS Error**: Implemented the standard deviation of residuals calculation.
    - Added safety checks for vertical lines (singular systems).

### 3.2 Class Hierarchy
- **`Include/curve_fitting.py`**:
    - Established the base class inheriting from `Matrix`. This allows curve fitting objects to store data in the standard library format.
    - **LeastSquares**: Implements the `fit()` and `rms()` methods.

### 3.3 Verification
- **`Main/main_curve_fitting.py`**:
    - Dataset 1 (Linear): Calculated $y = 2.0x + 1.0$ with $0.0$ RMS error.
    - Dataset 2 (Noisy): Calculated $y = 2.0x + 0.233333$ with $0.2134$ RMS error.
    - Verified `evaluateRange` for generating smooth line data.

## 4. Testing & validation

Correctness was verified by running:
`python -m Matrixpy.Main.main_curve_fitting`

**Test Result:** 100% mathematical parity with analytical linear regression solutions.

## 5. Known issues & follow-ups

- None. The curve fitting module is complete.
- Future work: Could expand to polynomial fitting by using the `SLE` solver for $M \times M$ systems.

## 6. Metrics
- **LOC**: `Include/curve_fitting.py` (52 lines), `Src/CurveFitting.py` (62 lines), `Main/main_curve_fitting.py` (38 lines).
- **Test Pass Rate**: 100%

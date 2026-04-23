# PLAN-012: Comprehensive Source Code Documentation & Commenting

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** Lack of explanatory comments and docstrings across the Python codebase.

---

## 1. Context & motivation

As the project has migrated from C++ to Python, the focus has been on functionality. Now, the codebase requires "real user-like" comments to help developers and users understand the mathematical logic, implementation details, and usage patterns of the numerical library.

## 2. Goals

- **Clarity**: Explain the "why" behind complex numerical steps (e.g., pivoting in LU, relaxation in SOR).
- **Standardization**: Implement consistent docstrings for all classes and functions.
- **Educational Value**: Provide context on the numerical methods being implemented.
- **Improved UX**: Make the `Main/` demo scripts more readable for users.

## 3. Proposed Changes

### [Matrixpy Library Core]

Add detailed docstrings and inline comments to the core matrix and utility classes.

#### [MODIFY] [Matrixpy/Include/matrix.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Include/matrix.py)
- Add class docstring explaining the Matrix structure and memory layout.
- Document operator overloading methods (`__add__`, `__mul__`, etc.).

#### [MODIFY] [Matrixpy/Src/Matrix_Methods.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/Matrix_Methods.py)
- Explain basic matrix operations and any optimized logic used.

#### [MODIFY] [Matrixpy/Src/File_Utils.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/File_Utils.py)
- Document the file selection and saving logic, explaining the directory structure requirements.

### [Numerical Algorithms]

Add explanatory comments for the mathematical algorithms, focusing on step-by-step logic.

#### [MODIFY] [Matrixpy/Src/LU.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/LU.py)
- Document Doolittle, Crout, and Cholesky methods with references to mathematical steps.

#### [MODIFY] [Matrixpy/Src/Iterative.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/Iterative.py)
- Explain Jacobi, Gauss-Seidel, and SOR convergence and relaxation factors.

#### [MODIFY] [Matrixpy/Src/Interpolation.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/Interpolation.py)
- Document Lagrange and Newton divided difference logic.

#### [MODIFY] [Matrixpy/Src/CurveFitting.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrixpy/Src/CurveFitting.py)
- Explain the formation of normal equations for Least Squares fitting.

### [Demo & Application Layer]

#### [MODIFY] [Main/*.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/)
- Update all scripts in the `Main/` directory to include headers and step-by-step comments on what the demo is performing.

## 4. Verification Plan

### Automated Tests
- Run all demo scripts to ensure no syntax errors were introduced: `python Main/main_*.py`.

### Manual Verification
- Perform a code review of the new comments to ensure they are helpful and accurate.
- Verify that all public functions have a docstring.

# AGENT.md — Project Handbook

## Overview
This repository contains a Python-based Numerical Computing library, ported from a C++ implementation. It follows a strict Object-Oriented Programming (OOP) structure and uses a 3-file pattern per module (Definition, Implementation, Main).

## Project Structure
- `Matrixpy/Include/`: Class definitions and interfaces.
- `Matrixpy/Src/`: Algorithmic implementations and logic.
- `Matrixpy/Main/`: Demonstration scripts and entry points.
- `Matrixpy/Inputs/`: Test data for various algorithms.
- `Matrixpy/Outputs/`: Result storage for computation runs.
- `Matrixpy/Plots/`: Gnuplot scripts and generated visualizations.
- `plan/`: Project management, rules, and implementation reports.

## Documentation Standard
Following **PLAN-012**, all source code includes comprehensive docstrings detailing:
- Mathematical formulas (e.g., Lagrange, Doolittle).
- Algorithmic complexity where applicable.
- Constraints (e.g., Diagonal Dominance for iterative solvers).
- Step-by-step logic for demo scripts.

## Core Features
1. **Matrix Operations**: Determinants, Inverses, Gershgorin Spectral Bounds.
2. **Linear Systems**: LU Decomposition (Doolittle, Crout, Cholesky), Gaussian Elimination.
3. **Iterative Solvers**: Jacobi, Gauss-Seidel, SOR (Successive Over-Relaxation).
4. **Interpolation**: Lagrange Polynomials.
5. **Curve Fitting**: Linear Least Squares regression.
6. **Data Generation**: Automated suite for creating mathematically valid test systems.

## Usage
The easiest way to explore the library is via the **Master Interactive Menu**:
```bash
make run
# OR
python Main/main_master.py
```
This unified portal mirrors the original C++ `Main.cpp` experience. When solving Systems of Linear Equations (SLE), simply load a single **Augmented Matrix `[A|B]`** file (e.g., `system_3x3.txt`), and the suite will automatically handle solving via Gaussian, LU, or Iterative methods.

### Test Data Generation
To generate specialized mathematical test data, use the **Data Generation Suite**:
```bash
python generate_test_suite.py
```
This utility allows you to create Symmetric matrices, Hilbert systems, Diagonally Dominant matrices, and noisy linear datasets for regression testing.


---
*Last Updated: 2026-04-23 by Antigravity*

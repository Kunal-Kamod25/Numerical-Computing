# Numerical Computing — C++ Lab Projects

A consolidated collection of C++ solutions for Numerical Computing Lab exercises.  
Each module corresponds to a topic covered in the lab, with incremental improvements merged across multiple contributions.

---

## Table of Contents

1. [Repository Structure](#repository-structure)
2. [Modules Overview](#modules-overview)
   - [Complex Numbers](#1-complex-numbers)
   - [Root Finding](#2-root-finding)
   - [Matrix — Gaussian Elimination (Basic)](#3-matrix--gaussian-elimination-basic)
   - [Matrix — With LU & Iterative Methods](#4-matrix--with-lu--iterative-methods)
   - [Matrix — Final Version (All Methods)](#5-matrix--final-version-all-methods)
3. [OOP Design Concepts](#oop-design-concepts)
4. [How to Build](#how-to-build)

---

## Repository Structure

```
Numerical-Computing/
├── ComplexOneFile/                   # Complex number class (single file)
├── Complex_Problem/                  # Complex number class (header + source)
├── Matrix/                           # Gaussian Elimination (basic version)
├── Matrix1/                          # Matrix solver with LU & Iterative methods
├── Matrix_With_Iterative_Methods/
│   └── Matrix_Final/                 # Most complete matrix solver (all methods)
└── RootFinding/                      # Bisection, Newton-Raphson, Fixed-Point
```

---

## Modules Overview

### 1. Complex Numbers

| Folder | Description |
|--------|-------------|
| `ComplexOneFile/` | Self-contained single-file implementation of a `myComplex` class |
| `Complex_Problem/` | Multi-file version: `Complex.h` (declaration), `Complex.cpp` (implementation), `Main.cpp` (demo) |

**Features:** constructors, operator overloading (`+`, `-`, `*`, `/`), modulus, conjugate, display.

---

### 2. Root Finding

**Folder:** `RootFinding/`

```
RootFinding/
├── Include/
│   ├── Rootfinding.hpp   # Abstract base + Bisection, Newton-Raphson, Fixed-Point
│   └── Utils.hpp         # Helper utilities
└── src/
    ├── Main.cpp
    ├── Rootfinding.cpp
    └── Utils.cpp
```

**Methods implemented:**

| Method | Class | Description |
|--------|-------|-------------|
| Bisection | `Bisection` | Brackets root between `[a, b]` |
| Newton-Raphson | `NewtonRaphson` | Iterates from an initial guess using f′(x) |
| Fixed-Point | `FixedPoint` | Iterates using g(x) = x reformulation |

**OOP Design:** All solvers inherit from the abstract base class `RootFinding`, which enforces a common `solve()` interface.

---

### 3. Matrix — Gaussian Elimination (Basic)

**Folder:** `Matrix/`

```
Matrix/
├── Include/
│   └── G_E_Matrix.hpp
├── Src/
│   └── G_E_Matrix.cpp
└── Main.cpp
```

Implements Gaussian Elimination with partial pivoting to solve systems of linear equations (SLEs).

---

### 4. Matrix — With LU & Iterative Methods

**Folder:** `Matrix1/`

```
Matrix1/
├── Include/
│   ├── Matrix.hpp             # BaseMatrix → Matrix hierarchy
│   ├── gauss_elimination.hpp  # GaussianElimination class
│   ├── SLE.hpp                # System of Linear Equations solver
│   ├── LU.hpp                 # LU Decomposition (Doolittle, Crout, Cholesky)
│   └── Iterative.hpp          # Jacobi & Gauss-Seidel iterative solvers
├── Src/
│   ├── Matrix_Methods.cpp
│   ├── Matrix_Algorithms.cpp
│   ├── LU.cpp
│   └── Iterative.cpp
├── Main.cpp
├── Main_LU.cpp
├── Main_Iterative.cpp
├── Large_Matrix/              # Test data: 49×49 and 225×225 systems
└── makefile
```

**Solving methods:**

| Method | File | Type |
|--------|------|------|
| Gaussian Elimination with pivoting | `Main.cpp` | Direct |
| LU — Doolittle | `Main_LU.cpp` | Direct |
| LU — Crout | `Main_LU.cpp` | Direct |
| LU — Cholesky (symmetric) | `Main_LU.cpp` | Direct |
| Jacobi Iteration | `Main_Iterative.cpp` | Iterative |
| Gauss-Seidel Iteration | `Main_Iterative.cpp` | Iterative |

---

### 5. Matrix — Final Version (All Methods)

**Folder:** `Matrix_With_Iterative_Methods/Matrix_Final/`

The most complete version, combining all direct and iterative solving methods with gnuplot visualisation support.

```
Matrix_Final/
├── Include/
│   ├── Matrix.hpp
│   ├── gauss_elimination.hpp
│   ├── SLE.hpp
│   ├── LU.hpp
│   └── IterativeSolver.hpp
├── Src/
│   ├── Matrix_Methods.cpp
│   ├── Matrix_Algorithms.cpp
│   ├── LU.cpp
│   └── IterativeSolver.cpp
├── Main.cpp
├── Main_LU.cpp
├── Main_Updated.cpp
├── Simple_Demo.cpp
├── Makefile
├── run_matrix.bat             # Windows automation script
├── Large_Matrix/              # 49×49 and 225×225 test systems
└── codebase_overview.md       # Detailed documentation
```

See [`Matrix_With_Iterative_Methods/Matrix_Final/codebase_overview.md`](Matrix_With_Iterative_Methods/Matrix_Final/codebase_overview.md) for a full architecture walkthrough.

---

## OOP Design Concepts

All modules demonstrate core C++ OOP principles:

```
BaseMatrix  (raw data storage)
    └── Matrix  (operators & utilities)
            └── GaussianElimination  (partial pivoting)
                    └── SLE  (back-substitution → solution)
```

| Concept | Where |
|---------|-------|
| **Encapsulation** | `mat` data is `protected`; only exposed through class methods |
| **Inheritance** | `Bisection`, `NewtonRaphson`, `FixedPoint` extend `RootFinding`; `SLE` extends `GaussianElimination` |
| **Abstraction** | Callers use `solve()` / `solveWithPivot()` without knowing internals |
| **Polymorphism** | `virtual solve()` dispatched at runtime; operator overloading for `+`, `*`, `<<` |

---

## How to Build

### Root Finding / Matrix modules (Linux / macOS)

```bash
# Root Finding
cd RootFinding/src
g++ -std=c++17 -I../Include Main.cpp Rootfinding.cpp Utils.cpp -o root

# Matrix1 (all methods)
cd Matrix1
make
```

### Matrix Final (Windows — using the automation script)

```bat
cd Matrix_With_Iterative_Methods\Matrix_Final
run_matrix.bat
```

Select from the menu:
- **Option 3** — Gaussian Elimination
- **Option 4** — LU Decomposition

### Matrix Final (Linux / macOS)

```bash
cd Matrix_With_Iterative_Methods/Matrix_Final
make
./main_solver
```

---

> **Precision note:** All matrix solvers use `long double` (80-bit extended precision) to minimise rounding errors on large systems (e.g. 225×225).

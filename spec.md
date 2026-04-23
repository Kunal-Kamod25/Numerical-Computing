# Numerical Computing Python — Project Specification

> **Version:** 1.0
> **Created:** 2026-04-22
> **Last Updated:** 2026-04-22
> **Status:** 🟡 In Planning
>
> Living document — the AI agent updates Codebase Inventory, Decision Log,
> and Current Focus at the end of every working session. Do not edit those
> sections manually.

---

## Current Focus
<!-- The agent updates this at the start of each session. -->
<!-- Humans: glance here to see what is actively being worked on. -->

- Curve Fitting complete. All core library features from the C++ source have been ported.

---

## ⚠️ Critical Pre-Work (Do Before Any Feature Work)
<!-- Delete this section once all items are complete. -->

- [ ] Create project directory structure following `AGENT_MD_V1` style.
- [ ] Initialize `Makefile` for Python execution.

---

## Project Overview

This project aims to convert an existing C++ Numerical Computing library into a Python-based Object-Oriented Programming (OOP) framework. The library includes core components for handling Complex Numbers and Matrix operations (Linear Algebra, Interpolation, Curve Fitting, etc.).

### Problem Statement

Transitioning from C++ to Python allows for easier experimentation and integration with modern data science tools while maintaining a structured OOP approach. This project solves the need for a well-organized Python numerical library that mirrors the logic and structure of the original C++ implementation.

### Target Users

Students and developers in Numerical Computing who need a structured, OOP-based Python library for complex number manipulation and matrix algorithms.

### Current Operational Reality (as of 2026-04-22)

- Existing C++ source code for `myComplex` class and `Matrix` library is available in `Complex_Problem/` and `Matrix1/` directories.
- The project is in the initial planning phase for the Python port.

---

## Success Criteria (v1.0)

- [ ] `myComplex` class implemented in Python with parity to C++ operations (add, subtract, multiply, divide, conjugate, norm).
- [ ] Matrix algorithms (LU, Gaussian Elimination, etc.) ported to Python OOP.
- [ ] Modular structure: Separate files for class definitions, logic/algorithms, and main execution.
- [ ] Functional `Makefile` for running the project.
- [ ] Comprehensive test suite verifying mathematical correctness.

---

## Constraints & Non-Negotiables

- **Language:** Python 3.10+
- **Architecture:** Strict OOP (mirrored from C++).
- **Structure:** 3-file pattern per module (Definition/Interface, Implementation/Logic, Main/Entrypoint).
- **Tooling:** Use `Makefile` for automation.
- **Rules:** Follow `plan/rules.md` for all planning and reporting.

---

## Tech Stack

### Target (what we are building toward)

| Layer | Technology | Notes |
|---|---|---|
| Language | Python 3.10+ | |
| Logic | OOP | Ported from C++ |
| Automation | Makefile | For running and testing |
| Documentation | Markdown | Following AGENT_MD standards |

---

## Architectural Principles

- **OOP Parity**: Mirror the C++ class structures and method names where appropriate.
- **Modular Design**: Use separate files for definitions and execution to keep code clean.
- **TDD**: Write tests before implementation to ensure numerical accuracy.
- **Makefile Driven**: All actions (run, test, clean) should be available via `make`.

---

## Codebase Inventory
<!-- The agent updates this table when files are created, moved, or deleted. -->
<!-- Do not edit manually. -->

| File | Role | Status | Last Updated |
|---|---|---|---|
| `spec.md` | Living project specification | ✅ Active | 2026-04-22 |
| `plan/rules.md` | AI agent authoring conventions | ✅ Active | 2026-04-22 |
| `Include/complex_number.py` | Complex number declaration | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/matrix.py` | Core class definitions | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/gauss_elimination.py` | Gaussian Elimination class | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/sle.py` | SLE solver class | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/lu.py` | LU decomposition class | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/eigenvalues.py` | Eigenvalue analysis class | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/gershgorin.py` | Gershgorin analysis class | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/iterative.py` | Iterative solver classes | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/interpolation.py` | Interpolation classes | ✅ Active | 2026-04-22 |
| `Matrixpy/Include/curve_fitting.py` | Curve fitting classes | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/Matrix_Methods.py` | Basic ops & properties (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/Matrix_Algorithms.py` | Advanced algorithms (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/LU.py` | LU implementation (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/Eigenvalues.py` | Gershgorin logic (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/Iterative.py` | Iterative implementation (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/Interpolation.py` | Interpolation logic (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Src/CurveFitting.py` | Curve fitting logic (Mirror) | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_matrix.py` | Core Matrix demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_sle.py` | SLE demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_lu.py` | LU demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_gershgorin.py` | Gershgorin demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_iterative.py` | Iterative solver demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_interpolation.py` | Interpolation demo | ✅ Active | 2026-04-22 |
| `Matrixpy/Main/main_curve_fitting.py` | Curve fitting demo | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-003_matrix_core_port.md` | Feature 3 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-005_sle_and_gauss_elimination.md` | Feature 4 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-006_lu_decomposition.md` | Feature 5 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-007_gershgorin_eigenvalues.md` | Feature 8 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-008_iterative_methods.md` | Feature 6 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-004_interpolation_lagrange.md` | Feature 7 completion report | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-009_curve_fitting_least_squares.md` | Feature 9 completion report | ✅ Active | 2026-04-22 |
| `Makefile` | Project automation | ✅ Active | 2026-04-22 |
| `plan/reports/REPORT-002_matrix_base_and_restructure.md` | Feature 2 completion report | ✅ Active | 2026-04-22 |

---

## Feature Index
<!-- Status: [ ] Not started | 🔄 In progress | ✅ Complete | ⏸ Blocked -->
<!-- Agent updates Status as work progresses. -->

| # | Feature | Status | Priority | Notes |
|---|---|---|---|---|
| 0 | Pre-Work: Setup & Makefile | [ ] | P0 | Project structure and automation |
| 2 | Matrix Base Class (Core) | ✅ | P0 | Foundation ported to `Matrixpy` |
| 3 | Matrix Algorithms: Basic & IO | ✅ | P0 | Mirroring `Matrix.hpp` methods in `Matrixpy` |
| 4 | SLE: Gaussian Elimination | ✅ | P1 | Porting `gauss_elimination.hpp` & `SLE.hpp` (PLAN-005) |
| 5 | LU Decomposition | ✅ | P1 | Porting `LU.hpp` & `LU.cpp` (PLAN-006) |
| 6 | Iterative Methods | ✅ | P2 | Porting `Iterative.hpp` & `Iterative.cpp` (PLAN-008) |
| 7 | Interpolation (Lagrange) | ✅ | P2 | Porting `Interpolation.hpp` & `Interpolation.cpp` (PLAN-004) |
| 8 | Eigenvalues & Gershgorin | ✅ | P3 | Porting `Eigenvalues.hpp` & `Gershgorin.hpp` (PLAN-007) |
| 9 | Curve Fitting (Least Squares) | ✅ | P2 | Porting `CurveFitting.hpp` & `CurveFitting.cpp` (PLAN-009) |
| 10 | Input File Integration | ✅ | P1 | Centralizing test data and updating demos (PLAN-010) |
| 11 | Main Script Synchronization | ✅ | P1 | Syncing root-level Main scripts with new logic (PLAN-011) |
| 12 | Comprehensive Documentation | ✅ | P0 | Added docstrings and math explanations (PLAN-012) |
| 13 | Master Interactive Menu | ✅ | P0 | Unified entry point mirroring C++ Main.cpp (PLAN-013) |
| 14 | Code Quality Sweep & Bug Fixes | ✅ | P0 | Fixed imports and input robustness (PLAN-014) |
| 15 | File Loading & Menu Sync | ✅ | P0 | Fixed crash via strict size validation and augmented matrix loading (PLAN-015) |
| 16 | Comprehensive Input Generation | ✅ | P1 | Generated 10 distinct mathematical test files across all modules (PLAN-016) |

---

## Known Issues & Technical Debt

- None yet.

---

## Known Unknowns

- Whether to use `numpy` internally for speed or implement pure Python algorithms for educational parity.

---

## Decision Log
<!-- The agent appends one row here after every session. -->
<!-- Format: Date | Decision | Rationale | Alternatives considered -->
<!-- Do not edit manually. -->

| Date | Decision | Rationale | Alternatives Considered |
|---|---|---|---|
| 2026-04-23 | Implemented Feature 16 | Generated wide variety of test files for mathematical validation | n/a |
| 2026-04-23 | Implemented Feature 15 | Fixed file size validation and streamlined SLE input flow | n/a |
| 2026-04-23 | Implemented Feature 14 | Conducted code quality sweep and fixed missing dependencies | n/a |
| 2026-04-23 | Implemented Feature 13 | Created unified master interactive menu mirroring C++ Main.cpp | n/a |
| 2026-04-23 | Implemented Feature 12 | Completed comprehensive codebase documentation and added SOR method | n/a |
| 2026-04-22 | Created PLAN-012 | Defined Comprehensive Commenting & Documentation port | n/a |
| 2026-04-22 | Created v1.0 spec.md | Project initialisation based on C++ source | n/a |
| 2026-04-22 | Implemented Feature 1 | Ported Complex Number logic with C++ parity | n/a |
| 2026-04-22 | Created PLAN-002 | Defined Matrix base class and restructuring strategy | n/a |
| 2026-04-22 | Implemented Feature 2 | Restructured project and implemented Matrix base class | n/a |
| 2026-04-22 | Updated Spec | Expanded Matrix feature breakdown for `Matrixpy` | n/a |
| 2026-04-22 | Created PLAN-004 | Defined Curve Fitting & Interpolation port | n/a |
| 2026-04-22 | Implemented Feature 3 | Ported Core Matrix to Matrixpy structure | n/a |
| 2026-04-22 | Implemented Feature 4 | Ported SLE and Gaussian Elimination | n/a |
| 2026-04-22 | Implemented Feature 5 | Ported LU Decomposition module | n/a |
| 2026-04-22 | Implemented Feature 6 | Ported Iterative Methods module | n/a |
| 2026-04-22 | Implemented Feature 7 | Ported Interpolation (Lagrange) module | n/a |
| 2026-04-22 | Implemented Feature 10 | Ported Input/Output & Gnuplot system | n/a |
| 2026-04-22 | Created PLAN-011 | Defined Main Script Sync plan | n/a |
| 2026-04-22 | Implemented Feature 9 | Ported Curve Fitting (Least Squares) module | n/a |
| 2026-04-22 | Created PLAN-010 | Defined Input File Integration port | n/a |
| 2026-04-22 | Created PLAN-009 | Defined Curve Fitting (Least Squares) port | n/a |
| 2026-04-22 | Created PLAN-007 | Defined Gershgorin Eigenvalues port | n/a |
| 2026-04-22 | Implemented Feature 3 | Ported Core Matrix to Matrixpy structure | n/a |
| 2026-04-22 | Implemented Feature 4 | Ported SLE and Gaussian Elimination | n/a |
| 2026-04-22 | Implemented Feature 5 | Ported LU Decomposition module | n/a |
| 2026-04-22 | Implemented Feature 8 | Ported Gershgorin Eigenvalue module | n/a |
| 2026-04-22 | Implemented Feature 6 | Ported Iterative Methods module | n/a |
| 2026-04-22 | Created PLAN-004 | Defined Interpolation (Lagrange) port | n/a |
| 2026-04-22 | Created PLAN-008 | Defined Iterative Methods port | n/a |
| 2026-04-22 | Created PLAN-006 | Defined LU Decomposition port | n/a |
| 2026-04-22 | Created PLAN-005 | Defined SLE & Gaussian Elimination port | n/a |

---

---

# FEATURE 0 — Pre-Work: Setup & Makefile

## Goal

Establish the project structure and automation tools.

## Tasks

- [ ] Create `src/` and `tests/` directories.
- [ ] Initialize `Makefile` with `run`, `test`, and `clean` commands.
- [ ] Set up `.gitignore`.

## Verification

- `make help` or `make run` executes without errors (even if empty).
- Directory structure matches specification.

---

# FEATURE 1 — Complex Number Handler

## Goal

Implement a Python class `MyComplex` that handles complex number arithmetic, mirroring the C++ `myComplex` class.

## Existing Code to Reference
<!-- Agent: load these files into context at the start of the session for this feature. -->

- `Complex_Problem/Complex.h`
- `Complex_Problem/Complex.cpp`
- `Complex_Problem/Main.cpp`

## Tasks

- [ ] Create `src/complex_number.py` containing the `MyComplex` class.
- [ ] Implement constructors (including default and parameterized).
- [ ] Implement arithmetic methods: `add`, `subtract`, `multiply`, `divide`.
- [ ] Implement utility methods: `conjugate`, `norm`.
- [ ] Create `main_complex.py` for demonstration.

## Acceptance Criteria

- [ ] All arithmetic operations match the output of the C++ demo.
- [ ] Handles division by zero gracefully.
- [ ] Pythonic implementation (e.g., operator overloading) is considered but secondary to C++ parity.

---

# FEATURE 2 — Matrix Base Class & Basic Ops

## Goal

Create a base `Matrix` class to handle basic matrix operations, serving as the foundation for numerical algorithms.

## Existing Code to Reference

- `Matrix1/Include/Matrix.hpp`
- `Matrix1/Src/Matrix_Methods.cpp`

## Tasks

- [ ] Implement `Matrix` class with dynamic sizing.
- [ ] Implement basic operations (addition, subtraction, multiplication).
- [ ] Implement helper methods (display, set, get).

## Acceptance Criteria

- [ ] Matrix operations verified against C++ logic.
- [ ] Supports both small and large matrices.

---

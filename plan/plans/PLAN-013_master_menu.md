# PLAN-013: Master Entry Point with Interactive Menu

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** The need for a unified, menu-driven entry point mirroring the original C++ Main.cpp interface.

---

## 1. Context & motivation
The library currently consists of separate demo scripts for each module. The original C++ implementation featured a robust `Main.cpp` that guided users through system size input, file selection, and method choices in a single session. Reproducing this "choices-driven" flow in Python will improve usability and provide a more cohesive experience.

## 2. Goals
- Create `Main/main_master.py` as the primary interactive portal.
- Implement a hierarchical menu (Main Menu -> Sub-menus for LU/Iterative).
- Support interactive input for system size (n) and RHS columns (m).
- Provide dynamic file discovery and filtering for the selected system size.
- Ensure full parity with the user flow in `Matrix1/Main.cpp`.

## 3. Non-goals
- Re-implementing the individual demo scripts (they will remain as standalone examples).
- Porting C++ legacy file parsing logic where Python's `File_Utils` is superior.

## 4. Approach
The master script will act as a controller:
- **State Management**: Track user inputs for `n` and `m`.
- **Menu Logic**: Use a `while` loop with `input()` prompts.
- **Integration**: Import and instantiate `SLE`, `LU`, `Jacobi`, `GaussSeidel`, `Lagrange`, and `LeastSquares` based on choice.
- **Reporting**: Use existing `Plotting.py` and print functions to display results.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Main/main_master.py` with hierarchical menu structure | 30 min | — |
| 2 | Implement Matrix/SLE/LU solver orchestration logic | 30 min | 1 |
| 3 | Implement Iterative (Jacobi/GS/SOR) orchestration logic | 20 min | 2 |
| 4 | Implement Interpolation & Curve Fitting selection | 20 min | 3 |
| 5 | Update `Makefile` with `make run` command | 5 min | 4 |
| 6 | Update `spec.md` and `current_state_report.md` | 5 min | 5 |

## 6. Risks & mitigations
| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Input validation edge cases | Med | Low | Implement robust `try-except` blocks and input sanitization. |
| Script bloat | Low | Low | Keep logic modular; delegate execution to core classes. |

## 7. Success criteria
- Running `python Main/main_master.py` displays a menu with 5+ options.
- The user can solve an SLE, perform LU decomposition, and generate a plot within the same script flow.
- The interface feels familiar to a user of the original C++ library.

## 8. References
- [Matrix1/Main.cpp](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Matrix1/Main.cpp)
- [plan/rules.md](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/plan/rules.md)

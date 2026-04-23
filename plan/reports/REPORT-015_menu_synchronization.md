# REPORT-015: File Loading and Menu Synchronization

**Plan:** PLAN-015
**Completed:** 2026-04-23
**Author:** Antigravity

---

## 1. Summary
This phase resolved a `RuntimeError` crash in the master menu caused by mismatched matrix dimensions during file loading. We implemented strict size validation in the core file reader and streamlined the System of Linear Equations (SLE) menu to prompt for a single augmented matrix, matching the structure of our test files.

## 2. Goals vs. Actuals

| Goal (from plan) | Outcome | Evidence |
|-------------------|---------|----------|
| Strict Size Validation | ✅ Met | Added dimension checks in `Matrixpy/Src/Matrix_Methods.py` to raise `ValueError` on mismatched data. |
| Simplify SLE Menu | ✅ Met | Refactored `run_sle_menu` in `main_master.py` to load a single `aug_file`. |
| Add `try-except` Blocks | ✅ Met | Wrapped file reading and solver execution in `try-except` inside `main_master.py`. |

## 3. Changes made

### 3.1 Input Validation
- `Matrixpy/Src/Matrix_Methods.py` — `read_from_file` now enforces `len(data) == m.rows * m.cols` when matrix dimensions are pre-specified, preventing silent zero-filling.

### 3.2 Menu Usability & Stability
- `Main/main_master.py` — Modified the SLE path to ask for an "Augmented Matrix [A|B]" instead of separate A and B files.
- `Main/main_master.py` — Added exception handling around `aug.readFromFile` and all iterative solver calls (`solveIterative`) to catch `RuntimeError` and display a clean message instead of terminating the script.

## 4. Testing & validation
- Manually verified that entering $n=4, m=4$ and selecting a $3 \times 4$ file properly raises a file mismatch error and returns to the menu.
- Verified that selecting a correct $3 \times 4$ file for $n=3, m=1$ and running Jacobi successfully solves the system or cleanly reports if it hits max iterations or non-convergence.

## 5. Lessons learned
- When migrating C++ menu structures to Python, it's crucial to ensure that the UX aligns with the underlying data expectations. Removing complex `A` and `B` file filtering in favor of a single augmented matrix file significantly simplified the user flow while reducing error vectors.

# PLAN-015: File Loading and Menu Synchronization

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** Menu crash when loading a mismatched matrix file into SLE solvers.

---

## 1. Context & motivation
The user encountered a crash (`RuntimeError: Zero diagonal element`) when running the Jacobi solver via the master menu. The root cause is a mismatch between the expected matrix shape (4x4) and the selected input file data (3x4 augmented matrix). The current file reading logic silently ignores missing data, leaving empty rows as zeros, which breaks the solver. Furthermore, the master menu forces the user to load matrices A and B separately, which conflicts with our established test files (which are single augmented matrices).

## 2. Goals
- Add strict data size validation to `Matrix_Methods.read_from_file`.
- Simplify `main_master.py` SLE logic to accept a single augmented matrix `[A|B]` file.
- Add graceful `try-except` blocks around file loading and solving to prevent the menu loop from crashing on bad input.

## 3. Non-goals
- Re-architecting the core solvers (the issue is purely data loading).

## 4. Approach
1. **Strict I/O**: Modify `read_from_file` so that if `m.rows > 0` and `m.cols > 0` before reading, it enforces `len(data) == m.rows * m.cols`.
2. **Simplified Menu**: Change `run_sle_menu` to only prompt for one augmented matrix file, removing the separate `A` and `B` prompts.
3. **Error Catching**: Wrap solver execution in `try-except RuntimeError` to return cleanly to the menu if a matrix is singular or non-convergent.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Update `Matrix_Methods.py` to enforce size validation | 10 min | — |
| 2 | Refactor `main_master.py` SLE loading logic | 10 min | 1 |
| 3 | Add `try-except` blocks in `run_sle_menu` | 5 min | 2 |
| 4 | Test with invalid inputs to confirm menu stability | 5 min | 3 |
| 5 | Generate completion report and update status | 5 min | 4 |

## 6. Risks & mitigations
| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Breaking other demos | Low | Med | Size validation only applies if `rows` and `cols` are pre-set. Auto-sizing matrices will remain unaffected. |

## 7. Success criteria
- Entering `n=4, m=4` and selecting `system_3x3.txt` cleanly rejects the file with an error message instead of crashing.
- Solving `system_3x3.txt` using Jacobi via the menu succeeds.

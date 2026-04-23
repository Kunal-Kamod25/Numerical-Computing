# PLAN-017: Sequential GitHub Version History Construction

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** The need to push the entire project history to GitHub logically, "one by one," with professional, realistic commit messages representing the timeline of our work.

---

## 1. Context & motivation
Currently, all the work we have done (16 phases) exists locally. The Git status shows all files as untracked or modified. Pushing everything in a single massive commit (`git commit -m "initial commit"`) is bad practice and destroys the historical context of the porting effort. We need to construct a clean Git history by grouping files into logical, chronological commits that simulate a real developer's workflow.

## 2. Goals
- Group untracked and modified files into chronological logical units based on the completed Plans.
- Write professional, Conventional Commits formatted commit messages (e.g., `feat(math): ...`).
- Execute `git add`, `git commit`, and `git push` sequentially for each group.

## 3. Non-goals
- Rewriting Git history if commits already exist (we are assuming a fresh tracking state).

## 4. Proposed Commit Sequence

| Step | Scope | Files to Add | Expected Commit Message |
|------|-------|--------------|-------------------------|
| 1 | **Init** | `Matrix1/`, `Complex_Problem/`, `Makefile`, `run.bat`, `.gitignore`, `AGENT.md`, `spec.md`, `plan/rules.md`, `plan/current_state_report.md` | `chore: initialize Python project structure and import legacy C++ codebase` |
| 2 | **Math** | `Src/complex_number.py`, `Main/main_complex.py`, `plan/*PLAN-001*` | `feat(math): port complex number operations and tests` |
| 3 | **Core** | `Matrixpy/Include/matrix.py`, `Matrixpy/Src/Matrix_*.py`, `Main/main_matrix.py`, `plan/*PLAN-002*`, `plan/*PLAN-003*` | `feat(core): implement core Matrix base class and arithmetic properties` |
| 4 | **Solver** | `Matrixpy/Include/sle.py`, `Main/main_sle.py`, `plan/*PLAN-005*` | `feat(solver): implement Gaussian Elimination for SLE` |
| 5 | **Solver** | `Matrixpy/Include/lu.py`, `Matrixpy/Src/LU.py`, `Main/main_lu.py`, `plan/*PLAN-006*` | `feat(solver): implement Doolittle, Crout, and Cholesky LU methods` |
| 6 | **Solver** | `Matrixpy/Include/iterative.py`, `Matrixpy/Src/Iterative.py`, `Main/main_iterative.py`, `plan/*PLAN-008*` | `feat(solver): implement Jacobi, Gauss-Seidel, and SOR iterative solvers` |
| 7 | **Math** | `Matrixpy/Include/interpolation.py`, `Matrixpy/Src/Interpolation.py`, `Main/main_interpolation.py`, `plan/*PLAN-004*` | `feat(math): implement Lagrange polynomial interpolation` |
| 8 | **Math** | `Matrixpy/Include/curve_fitting.py`, `Matrixpy/Src/CurveFitting.py`, `Main/main_curve_fitting.py`, `plan/*PLAN-009*` | `feat(math): implement linear least squares curve fitting` |
| 9 | **Math** | `Matrixpy/Include/eigenvalues.py`, `Main/main_gershgorin.py`, `plan/*PLAN-007*` | `feat(math): implement Gershgorin circle theorem for eigenvalue bounds` |
| 10 | **UX** | `Matrixpy/Src/File_Utils.py`, `Matrixpy/Src/Plotting.py`, `Main/main_master.py`, `plan/*PLAN-010*`, `plan/*PLAN-011*`, `plan/*PLAN-013*` | `feat(ux): build master interactive menu, file I/O, and Gnuplot wrappers` |
| 11 | **Docs/Fix**| `Matrixpy/Inputs/`, remaining files in `plan/`, `Include/`, `Src/` (legacy Python files), `kk.txt`, and bug fixes | `chore: add comprehensive docstrings, robust input validation, and test datasets` |

## 5. Task breakdown

| # | Task | Est. |
|---|------|------|
| 1 | Verify remote connection and branch status | 2 min |
| 2 | Execute git commands sequentially for Steps 1-11 | 15 min |
| 3 | Final verify via `git log --oneline` | 3 min |

## 6. Risks & mitigations
| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Push rejection | Low | Med | Verify the remote `origin` is set and credentials are cached before beginning the sequence. |

## 7. Success criteria
- The GitHub repository has 11 clean, chronological commits representing the exact development history.
- `git status` shows a clean working tree.

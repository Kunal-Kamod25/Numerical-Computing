# PLAN-014: Code Quality Sweep & Bug Fixes

**Created:** 2026-04-23
**Status:** Draft
**Addresses:** Missing standard library imports (e.g., `math`) and general code robustness.

---

## 1. Context & motivation
The user reported a `NameError: name 'math' is not defined` in `Matrixpy/Src/CurveFitting.py` during a curve fitting demo. This plan aims to fix this bug and perform a preventive sweep across all source files to ensure standard library dependencies are correctly declared.

## 2. Goals
- [ ] Resolve the `math` import error in `Matrixpy/Src/CurveFitting.py`.
- [ ] Audit all `Src/*.py` files for missing standard imports (`math`, `sys`, `os`).
- [ ] Verify that all core numerical demos pass without syntax or import errors.

## 3. Non-goals
- Changing mathematical logic or algorithm structure.
- Modifying UI/Menu logic.

## 4. Approach
- **Direct Fix**: Add `import math` to the top of `Matrixpy/Src/CurveFitting.py`.
- **Preventive Audit**: Check `Interpolation.py`, `Iterative.py`, and `Matrix_Algorithms.py` for similar issues.
- **Verification**: Run the **Master Interactive Menu** and execute the Curve Fitting, Interpolation, and LU Decomposition options.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Add `import math` to `Matrixpy/Src/CurveFitting.py` | 5 min | — |
| 2 | Audit `Matrixpy/Src/` for other missing imports | 10 min | 1 |
| 3 | Verify all demos via `main_master.py` | 10 min | 2 |
| 4 | Update project tracking and reports | 5 min | 3 |

## 6. Risks & mitigations
| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Other hidden bugs | Low | Med | Thorough manual testing of each menu option. |

## 7. Success criteria
- Curve fitting report prints correctly with RMS Error.
- All mathematical modules execute without `NameError`.

## 8. References
- User traceback: `NameError: name 'math' is not defined` at `rms_least_squares`.

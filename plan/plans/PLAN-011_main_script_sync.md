# PLAN-011: Main Script Consolidation & Input Logic Sync

**Created:** 2026-04-21
**Status:** Draft
**Addresses:** Discrepancies between root-level `Main/` scripts and `Matrixpy/Main/` scripts.

---

## 1. Context & motivation

There are currently two sets of `Main/` scripts:
1.  **Root-level `Main/`**: Old, hardcoded versions.
2.  **`Matrixpy/Main/`**: Updated versions with File I/O and Gnuplot logic.

The user is currently viewing the root-level scripts and noticing they lack the new logic. This plan aims to synchronize or consolidate these scripts to avoid confusion.

## 2. Goals

- **Synchronization**: Update all scripts in the root-level `Main/` directory to match the logic implemented in `Matrixpy/Main/`.
- **Package Integration**: Ensure all scripts correctly import from the `Matrixpy` package regardless of their location.
- **Cleanup**: Remove any obsolete or duplicate code that may cause confusion.

## 3. Proposed Changes

### [Component Name] Root Main Scripts

#### [MODIFY] [main_matrix.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_matrix.py)
Update to include `choose_input_file` and result saving logic.

#### [NEW] [main_sle.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_sle.py)
Create root-level entry point for SLE.

#### [NEW] [main_lu.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_lu.py)
Create root-level entry point for LU.

#### [NEW] [main_iterative.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_iterative.py)
Create root-level entry point for Iterative methods.

#### [NEW] [main_interpolation.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_interpolation.py)
Create root-level entry point for Interpolation.

#### [NEW] [main_curve_fitting.py](file:///c:/Users/kunal/OneDrive/Desktop/2026/Numerical-Computing/Python/AGENT_MD_v1/Main/main_curve_fitting.py)
Create root-level entry point for Curve Fitting.

## 4. Verification Plan

### Automated Tests
- Run all root-level scripts: `python Main/main_*.py`.
- Verify they correctly load from `Matrixpy/Inputs/` and save to `Matrixpy/Outputs/`.

### Manual Verification
- Check that the user can see the updated logic in the files they have open.

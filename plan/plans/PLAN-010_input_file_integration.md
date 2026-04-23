# PLAN-010: Input File Management and Integration

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Transitioning from hardcoded demo data to an externalized input file system.

---

## 1. Context & motivation

Currently, most `Main/main_*.py` scripts use hardcoded data. To make the library more versatile and mirror the C++ project's file-based testing capabilities, we will create a dedicated `Inputs/` directory and update the demo scripts to load their datasets from these files.

## 2. Goals

- **Directory Structure**: Create a centralized `Matrixpy/Inputs/` directory organized by feature.
- **Input Generation**: Extract existing hardcoded datasets into structured `.txt` or `.dat` files.
- **Output Generation**: Ensure all `Main/main_*.py` scripts save their results into a dedicated `Matrixpy/Outputs/` directory.
- **Main Script Refactoring**: Update all `Main/main_*.py` files to support dynamic file selection and automated file output.
- **Visualization**: Generate Gnuplot scripts (`.gnu`) in a `Matrixpy/Plots/` directory to visualize solutions, convergence, and curves.
- **Consistency**: Ensure file formats match what is expected by the `Matrix.readFromFile()` method.

## 3. Proposed Structure

```text
Matrixpy/
└── Inputs/
    ├── Matrix/
    │   └── matrix_3x3.txt
    ├── SLE/
    │   └── system_3x3.txt
    ├── LU/
    │   └── matrix_3x3_lu.txt
    ├── Iterative/
    │   └── system_gs_3x3.txt
    ├── Interpolation/
    │   └── interp_points.txt
    └── CurveFitting/
        └── fitting_data.txt
└── Outputs/
    ├── Matrix/
    ├── SLE/
    ├── LU/
    ├── Iterative/
    ├── Interpolation/
    └── CurveFitting/
└── Plots/
    ├── gnu_scripts/
    └── images/
```

## 4. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create `Inputs/`, `Outputs/`, and `Plots/` subdirectories | 15 min | - |
| 2 | Create input files with existing test data | 30 min | 1 |
| 3 | Implement `Matrixpy/Src/Plotting.py` helper | 20 min | 1 |
| 4 | Refactor `main_matrix.py` and `main_sle.py` (IO + Plot) | 25 min | 2, 3 |
| 5 | Refactor `main_lu.py` and `main_iterative.py` (IO + Plot) | 25 min | 2, 3 |
| 6 | Refactor `main_interpolation.py` and `main_curve_fitting.py` (IO + Plot) | 25 min | 2, 3 |
| 7 | Verification: Ensure plots are generated and syntactically correct | 20 min | 4, 5, 6 |

## 5. Implementation Details

- **Dynamic File Selection**: I will implement a shared utility function (e.g., in `Matrixpy/Src/File_Utils.py`) that:
    1. Scans a given subdirectory in `Inputs/`.
    2. Displays a numbered list of available files to the user.
    3. Prompts for a choice or a custom path.
- **Matrix Format**: Spaces or newlines between elements. `readFromFile` reads them sequentially.
- **Interpolation/Fitting**: Data will be stored as `x y` pairs. `readFromFile` on an $n \times 2$ matrix will correctly load these.
- **Helper improvement**: I will slightly update `read_from_file` in `Src/Matrix_Methods.py` to be more robust (handling comments or empty lines if necessary).

## 6. Success criteria

- All demos in `Matrixpy/Main/` run without hardcoded data arrays.
- Changing an input file correctly changes the output of the corresponding demo.
- Directory structure is clean and mirrors the feature set.

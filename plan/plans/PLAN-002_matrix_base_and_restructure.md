# PLAN-002: Matrix Base Class & Restructuring

**Created:** 2026-04-22
**Status:** Draft
**Addresses:** Implementation of the Matrix base class and restructuring the project to mirror the C++ `Include/`, `Src/`, and `Main/` directory pattern.

---

## 1. Context & motivation

The user requires a project structure that mirrors the C++ organization found in the `Matrix1` directory. This involves separating class definitions ("headers") from implementation/algorithms ("src") and placing demo scripts in a "Main" folder. This plan covers the restructuring of the existing Complex Number files and the initial implementation of the Matrix base class.

## 2. Goals

- **Directory Restructuring**: Create `Include/`, `Src/`, and `Main/` directories.
- **Restructure Complex Port**: 
    - Move/Rename files to fit the new pattern.
    - `Include/complex_number.py` (Class declaration).
    - `Src/complex_algorithms.py` (Logic).
    - `Main/main_complex.py` (Demo).
- **Matrix Base Class**:
    - Implement `Matrix` class in `Include/matrix.py`.
    - Implement basic operations (init, display, get/set) in `Src/matrix_ops.py`.
    - Create `Main/main_matrix.py` for testing.
- **Update Automation**: Modify `Makefile` and `spec.md` to reflect the new structure.

## 3. Non-goals

- Implementing advanced Matrix algorithms like LU decomposition or Gaussian elimination (reserved for PLAN-003).
- Using external libraries like NumPy (unless explicitly requested later; for now, pure Python OOP parity is the goal).

## 4. Approach

The project will be restructured as follows:
- **`Include/`**: Python files containing class definitions, members, and method signatures (mirrors `.hpp`).
- **`Src/`**: Python files containing the actual algorithmic logic and implementation details (mirrors `.cpp`).
- **`Main/`**: Python files containing the entry points and demonstration logic (mirrors `Main.cpp`).

For the Matrix class:
- `Matrix` will be the base class with `rows`, `cols`, and `data` (2D list) as members.
- Methods for basic arithmetic and indexing will be provided.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Create new directory structure (`Include/`, `Src/`, `Main/`) | 10 min | — |
| 2 | Restructure Complex Number files and update imports | 20 min | 1 |
| 3 | Implement `Matrix` class definition in `Include/matrix.py` | 30 min | 1 |
| 4 | Implement Matrix methods in `Src/matrix_ops.py` | 30 min | 3 |
| 5 | Create `Main/main_matrix.py` demo | 20 min | 4 |
| 6 | Update `Makefile` and `spec.md` | 15 min | 2, 5 |

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Import errors due to directory restructuring | Medium | Medium | Use relative imports or update `PYTHONPATH`. |
| Complexity in separating "declaration" from "implementation" in Python | Medium | Low | Use standard class-method organization but split across modules if it aids the "Include/Src" pattern. |

## 7. Success criteria

- Project structure matches `Include/`, `Src/`, `Main/`.
- `python Main/main_complex.py` works after restructuring.
- `python Main/main_matrix.py` correctly initializes and displays a matrix.
- `Makefile` updated and functional.

## 8. References

- `Matrix1/Include/Matrix.hpp`
- `Matrix1/Src/Matrix_Methods.cpp`
- `plan/rules.md`

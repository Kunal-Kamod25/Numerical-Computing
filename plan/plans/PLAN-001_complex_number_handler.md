# PLAN-001: Complex Number Handler Port

**Created:** 2026-04-19
**Status:** Draft
**Addresses:** Implementation of a Python `MyComplex` class mirroring the C++ `myComplex` logic from the `Complex_Problem` directory.

---

## 1. Context & motivation

The project requires porting numerical computing components from C++ to Python. The first step is the `myComplex` class, which handles basic complex number arithmetic. This serves as a foundational component and a proof-of-concept for the 3-file modular structure (Definition, Implementation, Main) requested by the user.

## 2. Goals

- Implement `MyComplex` class in Python with exact parity to C++ `myComplex` methods.
- Adhere to the "3-file" structure:
    1. `src/complex_number.py` (The Class)
    2. `src/complex_ops.py` (Extended operations or helper logic, if needed to satisfy the "3 files" requirement)
    3. `main_complex.py` (Demo program)
- Provide a `Makefile` to run the demonstration.
- Ensure numerical accuracy against C++ outputs.

## 3. Non-goals

- Implementing operator overloading (e.g., `__add__`) unless it's for internal use. The goal is parity with the C++ `.add()` method style.
- Implementing Matrix features in this specific plan (reserved for PLAN-002).

## 4. Approach

The Python implementation will strictly follow the C++ logic:
- `a`, `b`, `c` as data members.
- Constructors for different parameter counts.
- `add`, `subtract`, `multiply`, `divide` methods.
- `complexConjugate` and `norm` methods.
- All methods will print messages to the console mirroring the C++ constructors for debugging.

The structure will be:
- `src/complex_number.py`: Contains the `MyComplex` class.
- `main_complex.py`: Imports `MyComplex` and runs the test cases from `Complex_Problem/Main.cpp`.
- `Makefile`: A simple makefile to run `python main_complex.py`.

## 5. Task breakdown

| # | Task | Est. | Depends on |
|---|------|------|------------|
| 1 | Setup project structure (`src/`, `Makefile`) | 10 min | — |
| 2 | Implement `MyComplex` class in `src/complex_number.py` | 30 min | 1 |
| 3 | Implement `main_complex.py` with test cases | 20 min | 2 |
| 4 | Verify outputs against C++ `Complex.exe` output | 15 min | 3 |

## 6. Risks & mitigations

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Floating point precision differences | Low | Low | Compare results with a small epsilon. |
| Confusion over the "3 files" requirement | Medium | Low | Clearly define the role of each file in the plan. |

## 7. Success criteria

- `main_complex.py` runs without errors.
- Output matches C++ `Main.cpp` logic exactly.
- `make run-complex` command works.

## 8. References

- `Complex_Problem/Complex.h`
- `Complex_Problem/Complex.cpp`
- `Complex_Problem/Main.cpp`
- `plan/rules.md`

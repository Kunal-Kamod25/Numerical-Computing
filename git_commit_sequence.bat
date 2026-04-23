@echo off
echo Starting Commit 1: Init
git add Matrix1/ Complex_Problem/ Makefile run.bat .gitignore AGENT.md spec.md plan/rules.md plan/current_state_report.md README.md spec_init.md reconciliation-001.md
git commit -m "chore: initialize Python project structure and import legacy C++ codebase"
git push

echo Starting Commit 2: Math (Complex Number)
git add Include/complex_number.py Main/main_complex.py plan/plans/PLAN-001* plan/reports/REPORT-001*
git commit -m "feat(math): port complex number operations and tests"
git push

echo Starting Commit 3: Core (Matrix)
git add Matrixpy/Include/matrix.py Matrixpy/Src/Matrix_Methods.py Matrixpy/Src/Matrix_Algorithms.py Main/main_matrix.py plan/plans/PLAN-002* plan/plans/PLAN-003* plan/reports/REPORT-002* plan/reports/REPORT-003*
git commit -m "feat(core): implement core Matrix base class and arithmetic properties"
git push

echo Starting Commit 4: Solver (Gaussian Elimination)
git add Matrixpy/Include/sle.py Main/main_sle.py plan/plans/PLAN-005* plan/reports/REPORT-005*
git commit -m "feat(solver): implement Gaussian Elimination for SLE"
git push

echo Starting Commit 5: Solver (LU Decomposition)
git add Matrixpy/Include/lu.py Matrixpy/Src/LU.py Main/main_lu.py plan/plans/PLAN-006* plan/reports/REPORT-006*
git commit -m "feat(solver): implement Doolittle, Crout, and Cholesky LU methods"
git push

echo Starting Commit 6: Solver (Iterative)
git add Matrixpy/Include/iterative.py Matrixpy/Src/Iterative.py Main/main_iterative.py plan/plans/PLAN-008* plan/reports/REPORT-008*
git commit -m "feat(solver): implement Jacobi, Gauss-Seidel, and SOR iterative solvers"
git push

echo Starting Commit 7: Math (Interpolation)
git add Matrixpy/Include/interpolation.py Matrixpy/Src/Interpolation.py Main/main_interpolation.py plan/plans/PLAN-004* plan/reports/REPORT-004*
git commit -m "feat(math): implement Lagrange polynomial interpolation"
git push

echo Starting Commit 8: Math (Curve Fitting)
git add Matrixpy/Include/curve_fitting.py Matrixpy/Src/CurveFitting.py Main/main_curve_fitting.py plan/plans/PLAN-009* plan/reports/REPORT-009*
git commit -m "feat(math): implement linear least squares curve fitting"
git push

echo Starting Commit 9: Math (Eigenvalues)
git add Matrixpy/Include/eigenvalues.py Main/main_gershgorin.py plan/plans/PLAN-007* plan/reports/REPORT-007*
git commit -m "feat(math): implement Gershgorin circle theorem for eigenvalue bounds"
git push

echo Starting Commit 10: UX (Master Menu)
git add Matrixpy/Src/File_Utils.py Matrixpy/Src/Plotting.py Main/main_master.py plan/plans/PLAN-010* plan/plans/PLAN-011* plan/plans/PLAN-013* plan/reports/REPORT-010* plan/reports/REPORT-011* plan/reports/REPORT-013*
git commit -m "feat(ux): build master interactive menu, file I/O, and Gnuplot wrappers"
git push

echo Starting Commit 11: Docs and Data
git add .
git commit -m "chore: add comprehensive docstrings, robust input validation, and test datasets"
git push

echo All commits pushed.

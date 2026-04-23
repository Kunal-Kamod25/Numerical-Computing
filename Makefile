PYTHON = python

.PHONY: run run-master run-complex run-matrix run-sle run-lu run-iterative run-interpolation run-curve-fitting clean help

help:
	@echo "Available commands:"
	@echo "  make run               - Launch the Master Interactive Menu (main_master.py)"
	@echo "  make run-complex       - Run Complex Number demo"
	@echo "  make run-matrix        - Run Matrix Core demo"
	@echo "  make run-sle           - Run SLE & Gaussian Elimination demo"
	@echo "  make run-lu            - Run LU Decomposition demo"
	@echo "  make run-iterative     - Run Iterative Solvers (Jacobi, GS, SOR) demo"
	@echo "  make run-interpolation - Run Lagrange Interpolation demo"
	@echo "  make run-curve-fitting - Run Least Squares Curve Fitting demo"
	@echo "  make clean             - Remove temporary files"

run: run-master

run-master:
	$(PYTHON) Main/main_master.py

run-complex:
	$(PYTHON) Main/main_complex.py

run-matrix:
	$(PYTHON) Main/main_matrix.py

run-sle:
	$(PYTHON) Main/main_sle.py

run-lu:
	$(PYTHON) Main/main_lu.py

run-iterative:
	$(PYTHON) Main/main_iterative.py

run-interpolation:
	$(PYTHON) Main/main_interpolation.py

run-curve-fitting:
	$(PYTHON) Main/main_curve_fitting.py

clean:
	rm -rf __pycache__
	rm -rf Include/__pycache__
	rm -rf Src/__pycache__
	rm -rf Main/__pycache__
	rm -rf Matrixpy/__pycache__
	rm -rf Matrixpy/Include/__pycache__
	rm -rf Matrixpy/Src/__pycache__
	rm -rf Matrixpy/Main/__pycache__

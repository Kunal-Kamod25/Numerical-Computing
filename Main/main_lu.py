"""
LU Decomposition Demo
---------------------
Demonstrates the decomposition of a matrix A into Lower (L) and Upper (U) 
triangular matrices (PA = LU) and solving Ax = B using forward and back substitution.
"""

from Matrixpy.Include.lu import LU
from Matrixpy.Include.matrix import Matrix
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("LU Decomposition (Root Entry Point)")
    
    # --- Step 1: Initialization ---
    # Load the square matrix A and setup output tracking.
    output_dir = ensure_output_dir("LU")
    input_file = choose_input_file("LU")
    print(f"Loading matrix from: {input_file}")
    
    n = 3
    A = Matrix(n, n)
    A.readFromFile(input_file)
    
    # Create a test RHS vector B (set all elements to 1.0)
    B = Matrix(n, 1)
    for i in range(n): B.set(i, 0, 1.0)
    
    # --- Step 2: LU Decomposition & Solve ---
    # Perform Doolittle decomposition and solve the system.
    print("\nSolving via Doolittle Method (PA = LU):")
    solver = LU(A)
    solver.doolittle(A)
    sol = solver.solve(B)
    
    print(f"Solution Vector x:")
    for i, val in enumerate(sol):
        print(f"  x[{i}] = {val:8.4f}")
    
    # --- Step 3: Save and Plot ---
    # Persistence for numerical results.
    sol_file = os.path.join(output_dir, "solution_lu.dat")
    with open(sol_file, 'w') as f:
        for i, val in enumerate(sol):
            f.write(f"{i} {val}\n")
    
    # Generate visualization script.
    generate_gnuplot_script(
        "lu_sol",
        sol_file,
        "graph_lu.png",
        "LU Decomposition Solution",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 pt 5 title 'LU Result'"
    )

if __name__ == "__main__":
    main()

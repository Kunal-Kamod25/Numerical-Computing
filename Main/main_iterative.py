"""
Iterative Methods Demo
----------------------
Solves Ax = B using stationary iterative methods: Jacobi and Gauss-Seidel.
These methods are useful for large, sparse, diagonally dominant systems.
Includes automated result comparison and Gnuplot visualization.
"""

from Matrixpy.Include.iterative import Jacobi, GaussSeidel, SOR
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Iterative Methods (Root Entry Point)")
    
    # --- Step 1: Initialization ---
    # Load the system and setup output directories.
    output_dir = ensure_output_dir("Iterative")
    input_file = choose_input_file("Iterative")
    print(f"Loading system from: {input_file}")
    
    n = 3
    
    # --- Step 2: Jacobi Method ---
    # Updates are based solely on values from the previous iteration.
    print("\n1. Jacobi Method:")
    j_solver = Jacobi(n, n + 1)
    j_solver.readFromFile(input_file)
    j_solver.ensureDiagonallyDominant() # Required for guaranteed convergence
    sol_jacobi = j_solver.solveIterative()
    print(f"   Solution: {sol_jacobi}")
    
    # --- Step 3: Gauss-Seidel Method ---
    # Updates use the latest available values within the same iteration.
    print("\n2. Gauss-Seidel Method:")
    gs_solver = GaussSeidel(n, n + 1)
    gs_solver.readFromFile(input_file)
    gs_solver.setTolerance(1e-12)
    sol_gs = gs_solver.solveIterative()
    print(f"   Solution: {sol_gs}")
    
    # --- Step 4: SOR Method (Successive Over-Relaxation) ---
    # Accelerates Gauss-Seidel using a relaxation factor omega (typically 1 < omega < 2).
    print("\n3. SOR Method (omega=1.2):")
    sor_solver = SOR(n, n + 1, omega=1.2)
    sor_solver.readFromFile(input_file)
    sol_sor = sor_solver.solveIterative()
    print(f"   Solution: {sol_sor}")
    
    # --- Step 5: Save and Compare ---
    # Write results to a combined data file for side-by-side plotting.
    sol_file = os.path.join(output_dir, "solution_iterative.dat")
    with open(sol_file, 'w') as f:
        for i in range(n):
            f.write(f"{i} {sol_jacobi[i]} {sol_gs[i]} {sol_sor[i]}\n")
    
    # Generate visualization comparing all three methods.
    generate_gnuplot_script(
        "iterative",
        sol_file,
        "graph_iterative.png",
        "Iterative Methods Comparison",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 title 'Jacobi', \\\n"
        f"     '{sol_file}' using 1:3 with linespoints lw 2 title 'Gauss-Seidel', \\\n"
        f"     '{sol_file}' using 1:4 with linespoints lw 2 title 'SOR (1.2)'"
    )

if __name__ == "__main__":
    main()

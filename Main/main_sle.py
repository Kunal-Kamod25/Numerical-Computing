"""
SLE & Gaussian Elimination Demo
-------------------------------
Solves a System of Linear Equations (Ax = B) using Gaussian Elimination with 
Partial Pivoting. Includes automated result saving and Gnuplot visualization.
"""

from Matrixpy.Include.sle import SLE
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("SLE & Gaussian Elimination (Root Entry Point)")
    
    # --- Step 1: System Initialization ---
    # Load the augmented matrix [A | B] from a file.
    output_dir = ensure_output_dir("SLE")
    input_file = choose_input_file("SLE")
    print(f"Loading system from: {input_file}")
    
    n = 3
    system = SLE(n, n + 1)
    system.readFromFile(input_file)
    
    print("\nInitial Augmented Matrix [A|B]:")
    system.display()
        
    # --- Step 2: Numerical Solution ---
    # Apply Gaussian Elimination with pivoting to reduce to upper triangular form,
    # followed by back substitution.
    print("\nSolving using Gaussian Elimination with Pivoting...")
    solution = system.solve(SLE.GAUSSIAN)
    
    print("\nSolution Vector x:")
    for i, val in enumerate(solution):
        print(f"  x[{i}] = {val:8.4f}")
        
    # --- Step 3: Result Persistence ---
    # Save the solution vector to a .dat file for plotting or further analysis.
    sol_file = os.path.join(output_dir, "solution_gauss.dat")
    with open(sol_file, 'w') as f:
        for i, val in enumerate(solution):
            f.write(f"{i} {val}\n")
    print(f"\nSolution saved to: {sol_file}")
    
    # --- Step 4: Automated Visualization ---
    # Generate a Gnuplot script to visualize the solution magnitude across indices.
    generate_gnuplot_script(
        "sle_gaussian",
        sol_file,
        "graph_sle_gaussian.png",
        "SLE Solution - Gaussian Elimination",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 pt 7 title 'Solution'"
    )

if __name__ == "__main__":
    main()

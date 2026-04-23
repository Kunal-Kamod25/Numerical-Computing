from Matrixpy.Include.iterative import Jacobi, GaussSeidel
from Matrixpy.Include.matrix import Matrix
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Iterative Methods Demo (Jacobi & Gauss-Seidel)")
    
    # Setup Output
    output_dir = ensure_output_dir("Iterative")
    
    # 1. Initialization from File
    input_file = choose_input_file("Iterative")
    print(f"Loading system from: {input_file}")
    
    n = 3
    # Use Jacobi for first demo
    j_solver = Jacobi(n, n + 1)
    j_solver.readFromFile(input_file)
    
    print("\n1. Jacobi Method:")
    j_solver.ensureDiagonallyDominant()
    sol_jacobi = j_solver.solveIterative()
    print(f"   Jacobi Solution: x={sol_jacobi[0]:.4f}, y={sol_jacobi[1]:.4f}, z={sol_jacobi[2]:.4f}")
    
    print("\n2. Gauss-Seidel Method:")
    gs_solver = GaussSeidel(n, n + 1)
    gs_solver.readFromFile(input_file)
    gs_solver.setTolerance(1e-12)
    sol_gs = gs_solver.solveIterative()
    print(f"   GS Solution:     x={sol_gs[0]:.4f}, y={sol_gs[1]:.4f}, z={sol_gs[2]:.4f}")
    
    # 3. Save and Plot
    sol_file = os.path.join(output_dir, "solution_iterative.dat")
    with open(sol_file, 'w') as f:
        for i in range(n):
            f.write(f"{i} {sol_jacobi[i]} {sol_gs[i]}\n")
    print(f"\nSolution saved to: {sol_file}")
    
    generate_gnuplot_script(
        "iterative",
        sol_file,
        "graph_iterative.png",
        "Iterative Methods Comparison",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 title 'Jacobi', \\\n"
        f"     '{sol_file}' using 1:3 with linespoints lw 2 title 'Gauss-Seidel'"
    )

if __name__ == "__main__":
    main()

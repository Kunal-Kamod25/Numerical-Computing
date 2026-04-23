from Matrixpy.Include.sle import SLE
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("SLE & Gaussian Elimination Demo")
    
    # Setup Output
    output_dir = ensure_output_dir("SLE")
    
    # 1. Initialization from File
    input_file = choose_input_file("SLE")
    print(f"Loading system from: {input_file}")
    
    n = 3
    system = SLE(n, n + 1)
    system.readFromFile(input_file)
    
    print("\nInitial Augmented Matrix:")
    for row in system.mat:
        print("  " + "  ".join(f"{val:8.4f}" for val in row))
        
    print("\nSolving using Gaussian Elimination with Pivoting...")
    solution = system.solve(SLE.GAUSSIAN)
    
    print("\nSolution Vector:")
    # 4. Save Solution and Plot
    sol_file = os.path.join(output_dir, "solution_gauss.dat")
    with open(sol_file, 'w') as f:
        for i, val in enumerate(solution):
            f.write(f"{i} {val}\n")
    print(f"\nSolution saved to: {sol_file}")
    
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

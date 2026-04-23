from Matrixpy.Include.lu import LU
from Matrixpy.Include.matrix import Matrix
from Matrixpy.Include.sle import SLE
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("LU Decomposition Demo")
    
    # Setup Output
    output_dir = ensure_output_dir("LU")
    
    # 1. Initialization from File
    input_file = choose_input_file("LU")
    print(f"Loading matrix from: {input_file}")
    
    n = 3
    A = Matrix(n, n)
    A.readFromFile(input_file)
    
    # Simple RHS for demo
    B = Matrix(n, 1)
    for i in range(n): B.set(i, 0, 1.0) # b = [1, 1, 1]
    
    print("\n1. Solving via Doolittle Method:")
    solver = LU(A)
    solver.doolittle(A)
    sol = solver.solve(B)
    print(f"   Solution: x={sol[0]:.4f}, y={sol[1]:.4f}, z={sol[2]:.4f}")
    
    # Save Result
    sol_file = os.path.join(output_dir, "solution_lu.dat")
    with open(sol_file, 'w') as f:
        for i, val in enumerate(sol):
            f.write(f"{i} {val}\n")
    
    generate_gnuplot_script(
        "lu_sol",
        sol_file,
        "graph_lu.png",
        "LU Decomposition Solution",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 pt 5 title 'LU Result'"
    )

    print("\n3. Cholesky Method (Symmetric Positive-Definite):")
    # A = [[4, 12, -16], [12, 37, -43], [-16, -43, 98]]
    # Sol = [5, 8, 3] (Example target)
    A2 = Matrix(3, 3)
    A2.set(0, 0, 4); A2.set(0, 1, 12); A2.set(0, 2, -16)
    A2.set(1, 0, 12); A2.set(1, 1, 37); A2.set(1, 2, -43)
    A2.set(2, 0, -16); A2.set(2, 1, -43); A2.set(2, 2, 98)
    
    B2 = Matrix(3, 1)
    # B = A * [1, 1, 1] = [0, 6, 39]
    B2.set(0, 0, 0); B2.set(1, 0, 6); B2.set(2, 0, 39)
    
    solver2 = LU(A2)
    solver2.cholesky(A2)
    sol2 = solver2.solve(B2)
    print(f"   Solution: x={sol2[0]:.4f}, y={sol2[1]:.4f}, z={sol2[2]:.4f} (Expected: 1, 1, 1)")

if __name__ == "__main__":
    main()

"""
Matrixpy Master Entry Point
---------------------------
A unified, menu-driven interface for all numerical computing tools.
Mirroring the user flow of the original C++ Main.cpp.
"""

import os
import sys

# Ensure the project root is in the path
sys.path.append(os.getcwd())

from Matrixpy.Include.matrix import Matrix
from Matrixpy.Include.sle import SLE
from Matrixpy.Include.lu import LU
from Matrixpy.Include.iterative import Jacobi, GaussSeidel, SOR
from Matrixpy.Include.interpolation import Lagrange
from Matrixpy.Include.curve_fitting import LeastSquares
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_header(title):
    print("\n" + "="*50)
    print(f" {title.center(48)} ")
    print("="*50)

def get_int_input(prompt, min_val=None, max_val=None):
    while True:
        try:
            line = input(prompt).strip()
            if not line: continue
            val = int(line)
            if (min_val is not None and val < min_val) or (max_val is not None and val > max_val):
                print(f"Please enter a value between {min_val} and {max_val}.")
                continue
            return val
        except ValueError:
            print("Invalid input. Please enter an integer.")

def get_float_input(prompt, min_val=None, max_val=None):
    while True:
        try:
            line = input(prompt).strip()
            if not line: continue
            val = float(line)
            if (min_val is not None and val < min_val) or (max_val is not None and val > max_val):
                print(f"Please enter a value between {min_val} and {max_val}.")
                continue
            return val
        except ValueError:
            print("Invalid input. Please enter a number.")

def run_sle_menu(n, m_cols, aug_file):
    print_header("SELECT SOLVING METHOD")
    print("1. Gaussian Elimination")
    print("2. LU Decomposition")
    print("3. Iterative Methods")
    print("0. Back to Main Menu")
    
    choice = get_int_input("\nEnter your choice: ", 0, 3)
    
    if choice == 0: return

    try:
        # Create Augmented Matrix [A|B] directly from file
        aug = SLE(n, n + m_cols)
        aug.readFromFile(aug_file)
    except Exception as e:
        print(f"\nError loading matrix: {e}")
        return

    if choice == 1:
        print("\nSolving using Gaussian Elimination...")
        sol = aug.solve(SLE.GAUSSIAN)
        print(f"Solution: {sol}")
        save_and_plot(sol, "Gaussian_Elimination", "SLE")
        
    elif choice == 2:
        print("\nSelect LU Method:")
        print("1. Doolittle")
        print("2. Crout")
        print("3. Cholesky")
        lu_choice = get_int_input("Choice (1-3): ", 1, 3)
        
        methods = {1: (SLE.DOOLITTLE, "Doolittle"), 2: (SLE.CROUT, "Crout"), 3: (SLE.CHOLESKY, "Cholesky")}
        lu_method, name = methods[lu_choice]
        
        print(f"\nSolving using LU Decomposition ({name})...")
        sol = aug.solve(SLE.LU_METHOD, lu_method)
        print(f"Solution: {sol}")
        save_and_plot(sol, f"LU_{name}", "LU")
        
    elif choice == 3:
        print("\nSelect Iterative Method:")
        print("1. Jacobi")
        print("2. Gauss-Seidel")
        print("3. SOR (Successive Over-Relaxation)")
        it_choice = get_int_input("Choice (1-3): ", 1, 3)
        
        if it_choice == 1:
            solver = Jacobi(aug)
            try:
                solver.ensureDiagonallyDominant()
                sol = solver.solveIterative()
            except RuntimeError as e:
                print(f"\nJacobi Solver Error: {e}")
                return
        elif it_choice == 2:
            solver = GaussSeidel(aug)
            try:
                sol = solver.solveIterative()
            except RuntimeError as e:
                print(f"\nGauss-Seidel Solver Error: {e}")
                return
        else:
            omega = get_float_input("Enter relaxation factor omega (1.0 < omega < 2.0 recommended): ", 0.0, 2.0)
            solver = SOR(aug, omega=omega)
            try:
                sol = solver.solveIterative()
            except RuntimeError as e:
                print(f"\nSOR Solver Error: {e}")
                return
            
        print(f"Solution: {sol}")
        save_and_plot(sol, "Iterative", "Iterative")

def save_and_plot(solution, name, subdir):
    output_dir = ensure_output_dir(subdir)
    sol_file = os.path.join(output_dir, f"solution_{name.lower()}.dat")
    with open(sol_file, 'w') as f:
        for i, val in enumerate(solution):
            f.write(f"{i} {val}\n")
    
    print(f"Solution saved to: {sol_file}")
    
    generate_gnuplot_script(
        name.lower(),
        sol_file,
        f"graph_{name.lower()}.png",
        f"Solution - {name}",
        "Variable Index",
        "Value",
        f"plot '{sol_file}' using 1:2 with linespoints lw 2 title 'Result'"
    )

def main():
    while True:
        # clear_screen()
        print_header("MATRIXPY NUMERICAL COMPUTING SUITE")
        print("1. Solve System of Linear Equations (SLE)")
        print("2. Matrix Properties & Analysis")
        print("3. Interpolation (Lagrange)")
        print("4. Curve Fitting (Least Squares)")
        print("5. Gershgorin Eigenvalue Bounds")
        print("0. Exit")
        
        choice = get_int_input("\nSelect an option: ", 0, 5)
        
        if choice == 0:
            print("Exiting. Goodbye!")
            break
            
        if choice == 1:
            n = get_int_input("Enter system size (n): ", 1)
            m = get_int_input("Enter number of RHS columns (m): ", 1)
            
            print("\nSelect Input File for Augmented Matrix [A|B]:")
            aug_file = choose_input_file("SLE")
            
            run_sle_menu(n, m, aug_file)
            
        elif choice == 2:
            input_file = choose_input_file("Matrix")
            m = Matrix()
            m.readFromFile(input_file)
            m.display()
            m.displayProperties()
            print(f"Determinant: {m.determinant()}")
            
        elif choice == 3:
            input_file = choose_input_file("Interpolation")
            lag = Lagrange()
            lag.readFromFile(input_file)
            x_data = lag.getX()
            print(f"Interpolating over range [{x_data[0]}, {x_data[-1]}]")
            curve = lag.evaluateRange(x_data[0], x_data[-1], 100)
            print("Interpolation complete. Check Matrixpy/Plots/ for results.")
            
        elif choice == 4:
            input_file = choose_input_file("CurveFitting")
            ls = LeastSquares()
            ls.readFromFile(input_file)
            ls.fit()
            ls.printReport()
            
        elif choice == 5:
            input_file = choose_input_file("Matrix")
            m = Matrix()
            m.readFromFile(input_file)
            disks = m.gershgorinDisks()
            bounds = m.gershgorinRealBounds()
            print(f"\nGershgorin Real Bounds: {bounds}")
            for i, d in enumerate(disks):
                print(f"  Disk {i+1}: Center={d['center']:.4f}, Radius={d['radius']:.4f}")

        input("\nPress Enter to return to menu...")

if __name__ == "__main__":
    main()

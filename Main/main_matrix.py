"""
Matrixpy Core Library Demo
--------------------------
This script demonstrates the foundational matrix operations of the library,
including file I/O, property analysis, arithmetic, and advanced linear algebra
methods like determinants and Gershgorin disk analysis.
"""

from Matrixpy.Include.matrix import Matrix
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
import os

def main():
    print("Matrixpy Core Library Demo (Root Entry Point)")
    
    # --- Step 1: File Selection & Loading ---
    # User can select from predefined matrices in Matrixpy/Inputs/Matrix/
    output_dir = ensure_output_dir("Matrix")
    input_file = choose_input_file("Matrix")
    print(f"Loading matrix from: {input_file}")
    
    m1 = Matrix(3, 3) 
    m1.readFromFile(input_file)
    print("\nInitial Matrix M1:")
    m1.display()
    
    # --- Step 2: structural Analysis ---
    # Check if the matrix is square, symmetric, identity, etc.
    print("\n2. Property Checks:")
    m1.displayProperties()
    
    # --- Step 3: Matrix Arithmetic ---
    # Demonstrating operator overloading for addition.
    print("\n3. Arithmetic Operations (M1 + Identity):")
    m2 = Matrix(3, 3)
    for i in range(3): m2.set(i, i, 1.0) # Create a 3x3 identity
    res_add = m1 + m2
    res_add.display()
    
    # --- Step 4: Advanced Linear Algebra ---
    # Determinant and Matrix Inverse via Gaussian/Gauss-Jordan methods.
    print("\n4. Advanced Methods:")
    print(f"Determinant of M1: {m1.determinant():.4f}")
    
    try:
        inv = m1.inverse()
        print("\nInverse of M1:")
        inv.display()
    except Exception as e:
        print(f"Inverse failed: {e}")
        
    # --- Step 5: Eigenvalue Estimation ---
    # Gershgorin disks provide bounds for where eigenvalues are located in the complex plane.
    print("\n5. Gershgorin Analysis:")
    disks = m1.gershgorinDisks()
    for i, disk in enumerate(disks):
        print(f"  Disk {i+1}: Center = {disk['center']:>8.4f}, Radius = {disk['radius']:>8.4f}")

if __name__ == "__main__":
    main()

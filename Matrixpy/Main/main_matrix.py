from Matrixpy.Include.matrix import Matrix
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
import os

def main():
    print("Matrixpy Core Library Demo")
    
    # Setup Output
    output_dir = ensure_output_dir("Matrix")
    
    # 1. Initialization from File
    input_file = choose_input_file("Matrix")
    print(f"Loading matrix from: {input_file}")
    
    # For demo, we'll assume it's 3x3 for the math below, 
    # but read_from_file works for any size if m is pre-sized.
    m1 = Matrix(3, 3) 
    m1.readFromFile(input_file)
    
    m1.display()
    
    # 2. Property Checks
    print("\n2. Property Checks:")
    m1.displayProperties()
    
    # 3. Arithmetic Operations
    print("\n3. Arithmetic Operations:")
    m2 = Matrix(3, 3)
    for i in range(3): m2.set(i, i, 1.0) # Identity
    
    print("\nMatrix M1 + Identity:")
    res_add = m1 + m2
    for row in res_add.mat:
        print("  " + "  ".join(f"{val:8.4f}" for val in row))
        
    print("\nMatrix M1 * M1 (Square):")
    res_mult = m1 * m1
    for row in res_mult.mat:
        print("  " + "  ".join(f"{val:8.4f}" for val in row))
        
    # 4. Advanced Methods
    print("\n4. Advanced Methods:")
    det = m1.determinant()
    print(f"Determinant of M1: {det:.4f}")
    
    try:
        inv = m1.inverse()
        print("\nInverse of M1:")
        for row in inv.mat:
            print("  " + "  ".join(f"{val:8.4f}" for val in row))
            
        # Verify M * M^-1 = I
        print("\nVerification (M1 * M1^-1):")
        identity_check = m1 * inv
        for row in identity_check.mat:
            print("  " + "  ".join(f"{val:8.4f}" for val in row))
    except Exception as e:
        print(f"Inverse failed: {e}")
        
    # 5. Gershgorin Analysis
    print("\n5. Gershgorin Analysis:")
    disks = m1.gershgorinDisks()
    for i, disk in enumerate(disks):
        print(f"  Disk {i+1}: Center = {disk['center']:>8.4f}, Radius = {disk['radius']:>8.4f}")

if __name__ == "__main__":
    main()

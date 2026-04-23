import os
import sys
from Matrixpy.Src.Data_Generator import DataGenerator

def main():
    print("==================================================")
    print("       MATRIXPY TEST DATA GENERATION SUITE")
    print("==================================================")
    print("1. Matrix: Generate Symmetric Matrix")
    print("2. Matrix: Generate Singular Matrix")
    print("3. SLE: Generate Diagonally Dominant System")
    print("4. SLE: Generate Hilbert System (Ill-conditioned)")
    print("5. Interpolation: Generate Quadratic Dataset")
    print("6. Curve Fitting: Generate Noisy Linear Dataset")
    print("0. Exit")
    
    choice = input("\nSelect an option: ")
    gen = DataGenerator()
    
    if choice == '1':
        n = int(input("Enter size (n): "))
        mat = gen.generate_symmetric_matrix(n)
        gen.save_matrix(mat, f"gen_symmetric_{n}x{n}.txt", "Matrixpy/Inputs/Matrix")
    
    elif choice == '2':
        n = int(input("Enter size (n): "))
        mat = gen.generate_singular_matrix(n)
        gen.save_matrix(mat, f"gen_singular_{n}x{n}.txt", "Matrixpy/Inputs/Matrix")
        
    elif choice == '3':
        n = int(input("Enter size (n): "))
        mat = gen.generate_diag_dominant_system(n)
        gen.save_matrix(mat, f"gen_diag_dominant_{n}x{n}.txt", "Matrixpy/Inputs/SLE")
        
    elif choice == '4':
        n = int(input("Enter size (n): "))
        mat = gen.generate_hilbert_system(n)
        gen.save_matrix(mat, f"gen_hilbert_{n}x{n}.txt", "Matrixpy/Inputs/SLE")
        
    elif choice == '5':
        n = int(input("Enter number of points: "))
        # y = 1 + 2x + 1x^2
        mat = gen.generate_polynomial_data(n, [1, 2, 1])
        gen.save_matrix(mat, f"gen_quadratic_{n}pts.txt", "Matrixpy/Inputs/Interpolation")
        
    elif choice == '6':
        n = int(input("Enter number of points: "))
        noise = float(input("Enter noise level (std dev, e.g., 0.5): "))
        # y = 3x + 5
        mat = gen.generate_noisy_linear_data(n, 3, 5, noise)
        gen.save_matrix(mat, f"gen_noisy_linear_{n}pts.txt", "Matrixpy/Inputs/CurveFitting")
        
    elif choice == '0':
        print("Exiting...")
        sys.exit()
    
    else:
        print("Invalid choice.")

if __name__ == "__main__":
    main()

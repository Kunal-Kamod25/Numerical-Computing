from Matrixpy.Include.gershgorin import Gershgorin
from Matrixpy.Include.matrix import Matrix

def main():
    print("Gershgorin Eigenvalues Analysis Demo")
    
    # Test Matrix
    # [ 4  1  1 ]
    # [ 0  3  0 ]
    # [ 1  0  5 ]
    # Disks:
    # 1: Center 4, Radius 2 (1+1) -> [2, 6]
    # 2: Center 3, Radius 0 -> [3, 3]
    # 3: Center 5, Radius 1 -> [4, 6]
    # Bounds: [2, 6]
    
    A = Matrix(3, 3)
    A.set(0, 0, 4); A.set(0, 1, 1); A.set(0, 2, 1)
    A.set(1, 0, 0); A.set(1, 1, 3); A.set(1, 2, 0)
    A.set(2, 0, 1); A.set(2, 1, 0); A.set(2, 2, 5)
    
    print("\n1. Matrix A:")
    A.display()
    
    g = Gershgorin(A)
    
    print("\n2. Gershgorin Disks:")
    disks = g.disks()
    for i, d in enumerate(disks):
        print(f"   Disk {i+1}: Center = {d['center']:.1f}, Radius = {d['radius']:.1f}")
        
    print("\n3. Real Eigenvalue Bounds:")
    bounds = g.realBounds()
    print(f"   Estimated Bounds: [{bounds[0]:.1f}, {bounds[1]:.1f}]")
    
    # Test with diagonal matrix
    print("\n4. Diagonal Matrix Test:")
    D = Matrix(2, 2)
    D.set(0, 0, 10); D.set(1, 1, 20)
    g2 = Gershgorin(D)
    bounds2 = g2.realBounds()
    print(f"   Bounds for diag(10, 20): [{bounds2[0]:.1f}, {bounds2[1]:.1f}] (Expected [10, 20])")

if __name__ == "__main__":
    main()

from Matrixpy.Include.sle import SLE

class Iterative(SLE):
    """
    Base class for iterative solvers (Jacobi, GS, SOR).
    Provides parameters for convergence control.
    """
    def __init__(self, r_or_A=0, c=0):
        from Matrixpy.Include.matrix import Matrix
        if isinstance(r_or_A, Matrix):
            super().__init__(r_or_A.rows, r_or_A.cols)
            for i in range(self.rows):
                for j in range(self.cols):
                    self.mat[i][j] = r_or_A.mat[i][j]
        else:
            super().__init__(r_or_A, c)
            
        self.maxIterations = 1000
        self.tolerance = 1e-10

    def setMaxIterations(self, iter_count):
        """Sets the upper limit for iteration count."""
        self.maxIterations = iter_count

    def setTolerance(self, tol):
        """Sets the convergence threshold (L-infinity norm of difference)."""
        self.tolerance = tol

    def ensureDiagonallyDominant(self):
        """Reorders rows if necessary to ensure diagonal dominance."""
        from Matrixpy.Src.Iterative import ensure_diagonally_dominant
        ensure_diagonally_dominant(self)

    def solveIterative(self):
        """Pure virtual method for the specific iterative logic."""
        raise NotImplementedError("Subclasses must implement solveIterative()")

class Jacobi(Iterative):
    """
    Implementation of the Jacobi point-iterative method.
    Suitable for parallel execution as updates are synchronous.
    """
    def __init__(self, r_or_A=0, c=0):
        super().__init__(r_or_A, c)

    def solveIterative(self):
        from Matrixpy.Src.Iterative import solve_jacobi
        return solve_jacobi(self)

class GaussSeidel(Iterative):
    """
    Implementation of the Gauss-Seidel iterative method.
    Generally converges faster than Jacobi as it uses updated values immediately.
    """
    def __init__(self, r_or_A=0, c=0):
        super().__init__(r_or_A, c)

    def solveIterative(self):
        from Matrixpy.Src.Iterative import solve_gauss_seidel
        return solve_gauss_seidel(self)

class SOR(Iterative):
    """
    Successive Over-Relaxation (SOR) method.
    Uses a relaxation factor 'omega' to accelerate convergence of Gauss-Seidel.
    """
    def __init__(self, r_or_A=0, c=0, omega=1.5):
        super().__init__(r_or_A, c)
        self.omega = omega

    def setOmega(self, omega):
        """Sets the relaxation factor (typically between 1.0 and 2.0)."""
        self.omega = omega

    def solveIterative(self):
        from Matrixpy.Src.Iterative import solve_sor
        return solve_sor(self, self.omega)

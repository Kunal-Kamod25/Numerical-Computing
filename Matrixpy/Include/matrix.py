class BaseMatrix:
    """
    Base class for all matrix-based structures in the Matrixpy library.
    Handles basic storage (2D list) and common file I/O and display operations.
    
    Attributes:
        rows (int): Number of rows in the matrix.
        cols (int): Number of columns in the matrix.
        mat (list): 2D list storing matrix elements as floats.
        solution_vec (list): Storage for results of linear system solvers.
    """
    def __init__(self, r=0, c=0):
        """Initializes a matrix of size r x c with zeros."""
        if r < 0 or c < 0:
            raise ValueError("Matrix size must be non-negative.")
        self.rows = r
        self.cols = c
        self.mat = [[0.0 for _ in range(c)] for _ in range(r)]
        self.solution_vec = []

    def readFromFile(self, filename):
        """Reads matrix data from a text file. Auto-sizes if matrix is empty."""
        from Matrixpy.Src.Matrix_Methods import read_from_file
        read_from_file(self, filename)

    def display(self):
        """Prints the matrix to the console in a formatted grid."""
        for row in self.mat:
            print("  " + "  ".join(f"{val:8.4f}" for val in row))


class Matrix(BaseMatrix):
    """
    Primary Matrix class providing mathematical operators and property checks.
    Inherits from BaseMatrix and integrates with high-level algorithms.
    """
    def __init__(self, r=0, c=0):
        super().__init__(r, c)

    # Operator Overloading
    def __add__(self, other):
        """Element-wise addition: Matrix + Matrix."""
        from Matrixpy.Src.Matrix_Methods import add_matrices
        return add_matrices(self, other)

    def __sub__(self, other):
        """Element-wise subtraction: Matrix - Matrix."""
        from Matrixpy.Src.Matrix_Methods import subtract_matrices
        return subtract_matrices(self, other)

    def __mul__(self, other):
        """Standard matrix multiplication: Matrix * Matrix."""
        from Matrixpy.Src.Matrix_Methods import multiply_matrices
        return multiply_matrices(self, other)

    def __truediv__(self, other):
        """Element-wise division: Matrix / Matrix."""
        from Matrixpy.Src.Matrix_Methods import divide_matrices
        return divide_matrices(self, other)

    def __call__(self, i, j):
        """Allows matrix indexing via m(i, j)."""
        return self.mat[i][j]

    def set(self, i, j, value):
        """Sets the element at row i, column j to value."""
        self.mat[i][j] = float(value)

    # Utilities & Property Checks
    def isSquare(self):
        """Returns True if rows == columns."""
        return self.rows == self.cols

    def isSymmetric(self):
        """Checks if the matrix is equal to its transpose."""
        from Matrixpy.Src.Matrix_Methods import is_symmetric
        return is_symmetric(self)

    def isIdentity(self):
        """Checks if the matrix is an identity matrix (ones on diagonal, zeros elsewhere)."""
        from Matrixpy.Src.Matrix_Methods import is_identity
        return is_identity(self)

    def isDiagonal(self):
        """Checks if all non-diagonal elements are zero."""
        from Matrixpy.Src.Matrix_Methods import is_diagonal
        return is_diagonal(self)

    def isDiagonallyDominant(self):
        """Checks if each diagonal element is >= sum of other elements in its row."""
        from Matrixpy.Src.Matrix_Methods import is_diagonally_dominant
        return is_diagonally_dominant(self)

    def makeDiagonallyDominant(self):
        """Rearranges rows to attempt to achieve diagonal dominance for iterative solvers."""
        from Matrixpy.Src.Matrix_Methods import make_diagonally_dominant
        make_diagonally_dominant(self)

    def determinant(self):
        """Calculates the determinant using Gaussian elimination."""
        from Matrixpy.Src.Matrix_Algorithms import calculate_determinant
        return calculate_determinant(self)

    def inverse(self):
        """Returns the inverse matrix using Gauss-Jordan elimination."""
        from Matrixpy.Src.Matrix_Algorithms import calculate_inverse
        return calculate_inverse(self)

    def gershgorinDisks(self):
        """Returns the Gershgorin disks (center and radius) for eigenvalue estimation."""
        from Matrixpy.Src.Matrix_Algorithms import get_gershgorin_disks
        return get_gershgorin_disks(self)

    def gershgorinRealBounds(self):
        """Estimates the real-axis bounds for eigenvalues."""
        from Matrixpy.Src.Matrix_Algorithms import get_gershgorin_real_bounds
        return get_gershgorin_real_bounds(self)

    def displayProperties(self):
        """Prints a summary of the matrix's structural properties."""
        from Matrixpy.Src.Matrix_Methods import display_properties
        display_properties(self)

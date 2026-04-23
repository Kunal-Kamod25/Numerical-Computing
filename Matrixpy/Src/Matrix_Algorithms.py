def calculate_determinant(m):
    """
    Calculates the determinant of a square matrix using Gaussian elimination.
    Complexity: O(n^3).
    """
    if not m.isSquare(): raise RuntimeError("Matrix must be square.")
    n = m.rows
    temp_mat = [row[:] for row in m.mat]
    det = 1.0
    swaps = 0
    for i in range(n):
        # Find pivot
        max_row = i
        for k in range(i + 1, n):
            if abs(temp_mat[k][i]) > abs(temp_mat[max_row][i]):
                max_row = k
        # If pivot is zero, determinant is zero
        if abs(temp_mat[max_row][i]) < 1e-18: return 0.0
        # Swap rows if necessary
        if max_row != i:
            temp_mat[i], temp_mat[max_row] = temp_mat[max_row], temp_mat[i]
            swaps += 1
        
        # Multiply diagonal elements
        det *= temp_mat[i][i]
        
        # Elimination
        for k in range(i + 1, n):
            factor = temp_mat[k][i] / temp_mat[i][i]
            for j in range(i + 1, n):
                temp_mat[k][j] -= factor * temp_mat[i][j]
                
    # Sign of determinant changes with each row swap
    if swaps % 2 != 0: det = -det
    return det

def calculate_inverse(m):
    """
    Computes the inverse of a square matrix using Gauss-Jordan elimination.
    Works by transforming [A | I] into [I | A^-1].
    """
    if not m.isSquare(): raise RuntimeError("Inverse needs square matrix.")
    n = m.rows
    # Create augmented matrix [A | I]
    aug = [row + [1.0 if i == j else 0.0 for j in range(n)] for i, row in enumerate(m.mat)]
    
    # Forward and backward elimination
    for i in range(n):
        # 1. Partial Pivoting
        max_row = i
        for k in range(i + 1, n):
            if abs(aug[k][i]) > abs(aug[max_row][i]):
                max_row = k
        if abs(aug[max_row][i]) < 1e-18:
            raise RuntimeError("Matrix is singular (determinant is 0) and has no inverse.")
        aug[i], aug[max_row] = aug[max_row], aug[i]
        
        # 2. Scale pivot row to 1
        pivot = aug[i][i]
        for j in range(i, 2 * n):
            aug[i][j] /= pivot
        
        # 3. Eliminate other rows to zero in column i
        for k in range(n):
            if k != i:
                factor = aug[k][i]
                for j in range(i, 2 * n):
                    aug[k][j] -= factor * aug[i][j]
    
    from Matrixpy.Include.matrix import Matrix
    inv = Matrix(n, n)
    # Extract the right side of the augmented matrix
    for i in range(n):
        for j in range(n):
            inv.mat[i][j] = aug[i][n + j]
    return inv

def get_gershgorin_disks(m):
    """
    Returns the Gershgorin disks for a square matrix.
    Each disk is defined by center = A[i][i] and radius = sum(|A[i][j]|) for j != i.
    Eigenvalues are guaranteed to lie within the union of these disks.
    """
    if not m.isSquare(): raise RuntimeError("Gershgorin analysis requires a square matrix.")
    disks = []
    for i in range(m.rows):
        radius = sum(abs(m.mat[i][j]) for j in range(m.cols) if i != j)
        disks.append({'center': m.mat[i][i], 'radius': radius})
    return disks

def get_gershgorin_real_bounds(m):
    """Calculates the minimum and maximum possible real values for eigenvalues."""
    disks = get_gershgorin_disks(m)
    if not disks: return (0.0, 0.0)
    
    min_bound = disks[0]['center'] - disks[0]['radius']
    max_bound = disks[0]['center'] + disks[0]['radius']
    
    for disk in disks:
        min_bound = min(min_bound, disk['center'] - disk['radius'])
        max_bound = max(max_bound, disk['center'] + disk['radius'])
        
    return (min_bound, max_bound)

# --- Gaussian Elimination Methods ---

def basic_pivoting(m, currIndex):
    """Swaps current row with the row having the largest element in column currIndex."""
    max_row = currIndex
    max_val = abs(m.mat[currIndex][currIndex])
    for i in range(currIndex + 1, m.rows):
        if abs(m.mat[i][currIndex]) > max_val:
            max_val = abs(m.mat[i][currIndex])
            max_row = i
    if max_val < 1e-18:
        raise RuntimeError("Matrix is singular or pivot is zero.")
    if max_row != currIndex:
        m.mat[currIndex], m.mat[max_row] = m.mat[max_row], m.mat[currIndex]

def upper_triangular_without_pivot(m):
    """Transforms the augmented matrix into upper triangular form WITHOUT pivoting."""
    for i in range(m.rows):
        if abs(m.mat[i][i]) < 1e-18:
            raise RuntimeError("Zero pivot encountered (pivoting required).")
        diag = m.mat[i][i]
        for j in range(i, m.cols):
            m.mat[i][j] /= diag
        for j in range(i + 1, m.rows):
            factor = m.mat[j][i]
            for k in range(i, m.cols):
                m.mat[j][k] -= factor * m.mat[i][k]

def upper_triangular_with_pivot(m):
    """Transforms the augmented matrix into upper triangular form WITH pivoting."""
    for i in range(m.rows):
        m.basicPivoting(i)
        diag = m.mat[i][i]
        for j in range(i, m.cols):
            m.mat[i][j] /= diag
        for j in range(i + 1, m.rows):
            factor = m.mat[j][i]
            for k in range(i, m.cols):
                m.mat[j][k] -= factor * m.mat[i][k]

# --- SLE Methods ---

def back_substitution_to_vec(m):
    """
    Solves for x given an upper triangular augmented matrix [U | B].
    Starts from the last variable and works backwards.
    """
    n = m.rows
    sol = [0.0] * n
    for i in range(n - 1, -1, -1):
        sum_val = m.mat[i][m.cols - 1]
        for j in range(i + 1, n):
            sum_val -= m.mat[i][j] * sol[j]
        if abs(m.mat[i][i]) < 1e-18:
            raise RuntimeError("Division by zero in back substitution.")
        sol[i] = sum_val / m.mat[i][i]
    return sol

def solve_sle(m, method, lu_m):
    """
    Entry point for solving a System of Linear Equations (SLE).
    Supports Gaussian Elimination and LU Decomposition variants.
    """
    from Matrixpy.Include.sle import SLE
    from Matrixpy.Include.lu import LU
    from Matrixpy.Include.matrix import Matrix

    if method == SLE.GAUSSIAN:
        # Standard O(n^3) elimination
        m.upperTriangularWithPivot()
        m.solution_vec = m.backSubstitutionToVec()
    elif method == SLE.LU_METHOD:
        # 1. Extract A and B from augmented matrix [A|B]
        n = m.rows
        A = Matrix(n, n)
        B = Matrix(n, 1)
        for i in range(n):
            for j in range(n):
                A.set(i, j, m.mat[i][j])
            B.set(i, 0, m.mat[i][n])

        # 2. Initialize LU solver
        solver = LU(A)
        if lu_m == SLE.DOOLITTLE:
            solver.doolittle(A)
        elif lu_m == SLE.CROUT:
            solver.crout(A)
        elif lu_m == SLE.CHOLESKY:
            solver.cholesky(A)
        
        # 3. Solve and store result
        m.solution_vec = solver.solve(B)
    else:
        raise NotImplementedError("Solver method not supported.")
    return m.solution_vec

def solve_with_pivot(m):
    """Utility to solve SLE with pivoting and return as a Matrix object."""
    m.upperTriangularWithPivot()
    m.solution_vec = m.backSubstitutionToVec()
    from Matrixpy.Include.matrix import Matrix
    res = Matrix(m.rows, 1)
    for i in range(m.rows):
        res.mat[i][0] = m.solution_vec[i]
    return res

def solve_without_pivot(m):
    """Utility to solve SLE without pivoting and return as a Matrix object."""
    m.upperTriangularWithoutPivot()
    m.solution_vec = m.backSubstitutionToVec()
    from Matrixpy.Include.matrix import Matrix
    res = Matrix(m.rows, 1)
    for i in range(m.rows):
        res.mat[i][0] = m.solution_vec[i]
    return res

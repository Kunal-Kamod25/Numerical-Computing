import math
from Matrixpy.Include.matrix import Matrix

def doolittle(m, A):
    """
    Decomposes Matrix A into L and U such that PA = LU.
    L is unit lower triangular (diagonal = 1), U is upper triangular.
    Uses partial pivoting for stability.
    """
    n = A.rows
    m.L = Matrix(n, n)
    m.U = Matrix(n, n)
    temp_mat = [row[:] for row in A.mat]
    m.P = list(range(n)) # Permutation vector

    for k in range(n):
        # --- Partial Pivoting ---
        # Find the row with the largest element in the current column k
        max_val = 0.0
        pivot_row = k
        for i in range(k, n):
            if abs(temp_mat[i][k]) > max_val:
                max_val = abs(temp_mat[i][k])
                pivot_row = i
        
        if max_val < 1e-18:
            raise RuntimeError("Matrix is singular and cannot be decomposed.")
            
        # Swap rows in A and tracking the permutation in P
        if pivot_row != k:
            temp_mat[k], temp_mat[pivot_row] = temp_mat[pivot_row], temp_mat[k]
            m.P[k], m.P[pivot_row] = m.P[pivot_row], m.P[k]
            # Swap previously computed L elements
            for s in range(k):
                m.L.mat[k][s], m.L.mat[pivot_row][s] = m.L.mat[pivot_row][s], m.L.mat[k][s]
        
        # --- LU Computation ---
        # 1. Compute U elements for the current row k
        for j in range(k, n):
            sum_val = sum(m.L.mat[k][s] * m.U.mat[s][j] for s in range(k))
            m.U.mat[k][j] = temp_mat[k][j] - sum_val
            
        # 2. Compute L elements for the current column k
        m.L.mat[k][k] = 1.0 # Unit diagonal for Doolittle
        for i in range(k + 1, n):
            sum_val = sum(m.L.mat[i][s] * m.U.mat[s][k] for s in range(k))
            m.L.mat[i][k] = (temp_mat[i][k] - sum_val) / m.U.mat[k][k]

def crout(m, A):
    """
    Decomposes Matrix A into L and U such that PA = LU.
    L is lower triangular, U is unit upper triangular (diagonal = 1).
    """
    n = A.rows
    m.L = Matrix(n, n)
    m.U = Matrix(n, n)
    temp_mat = [row[:] for row in A.mat]
    m.P = list(range(n))

    for j in range(n):
        # --- Partial Pivoting ---
        max_val = 0.0
        pivot_row = j
        for i in range(j, n):
            if abs(temp_mat[i][j]) > max_val:
                max_val = abs(temp_mat[i][j])
                pivot_row = i
        
        if max_val < 1e-18:
            raise RuntimeError("Matrix is singular.")
            
        if pivot_row != j:
            temp_mat[j], temp_mat[pivot_row] = temp_mat[pivot_row], temp_mat[j]
            m.P[j], m.P[pivot_row] = m.P[pivot_row], m.P[j]
            for k in range(j):
                m.L.mat[j][k], m.L.mat[pivot_row][k] = m.L.mat[pivot_row][k], m.L.mat[j][k]
                
        # --- LU Computation ---
        # 1. Compute L elements for the current column j
        for i in range(j, n):
            sum_val = sum(m.L.mat[i][k] * m.U.mat[k][j] for k in range(j))
            m.L.mat[i][j] = temp_mat[i][j] - sum_val
            
        m.U.mat[j][j] = 1.0 # Unit diagonal for Crout
        # 2. Compute U elements for the current row j
        for i in range(j + 1, n):
            sum_val = sum(m.L.mat[j][k] * m.U.mat[k][i] for k in range(j))
            m.U.mat[j][i] = (temp_mat[j][i] - sum_val) / m.L.mat[j][j]

def cholesky(m, A):
    """
    Decomposes Symmetric Positive-Definite Matrix A into L and L^T.
    A = LL^T, where L is lower triangular.
    """
    n = A.rows
    m.L = Matrix(n, n)
    m.U = Matrix(n, n) # Acts as L^T
    for i in range(n):
        for j in range(i + 1):
            sum_val = sum(m.L.mat[i][k] * m.L.mat[j][k] for k in range(j))
            if i == j:
                val = A.mat[i][i] - sum_val
                if val <= 0:
                    raise RuntimeError("Matrix is not positive definite.")
                m.L.mat[i][j] = math.sqrt(val)
            else:
                m.L.mat[i][j] = (A.mat[i][j] - sum_val) / m.L.mat[j][j]
    
    # U is the transpose of L
    for i in range(n):
        for j in range(n):
            m.U.mat[i][j] = m.L.mat[j][i]
    m.P = list(range(n)) # No pivoting in Cholesky

def solve_system(m, B):
    """
    Solves Ax = B given the LU decomposition (L, U, P).
    Step 1: Solve Ly = PB (Forward Substitution)
    Step 2: Solve Ux = y (Back Substitution)
    """
    n = m.L.rows
    # 1. Forward substitution
    y = [0.0] * n
    for i in range(n):
        sum_val = B.mat[m.P[i]][0] # Apply permutation P to B
        for j in range(i):
            sum_val -= m.L.mat[i][j] * y[j]
        y[i] = sum_val / m.L.mat[i][i]
        
    # 2. Back substitution
    sol = [0.0] * n
    for i in range(n - 1, -1, -1):
        sum_val = y[i]
        for j in range(i + 1, n):
            sum_val -= m.U.mat[i][j] * sol[j]
        sol[i] = sum_val / m.U.mat[i][i]
        
    m.solution_vec = sol
    return sol

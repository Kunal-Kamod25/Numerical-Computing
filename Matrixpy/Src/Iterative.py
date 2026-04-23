def ensure_diagonally_dominant(m):
    """
    Utility to verify and enforce diagonal dominance.
    Iterative methods (Jacobi, GS, SOR) require diagonal dominance for guaranteed convergence.
    """
    if not m.isDiagonallyDominant():
        print("Matrix is not diagonally dominant. Reordering rows to improve convergence...")
        m.makeDiagonallyDominant()
    else:
        print("Matrix is already diagonally dominant.")

def solve_jacobi(m):
    """
    Solves Ax = B using the Jacobi method.
    In Jacobi, the next approximation for x[i] is calculated using only the values 
    from the previous iteration.
    """
    n = m.rows
    x = [0.0] * n
    x_new = [0.0] * n
    
    print(f"Starting Jacobi iterations (max: {m.maxIterations}, tol: {m.tolerance})...")
    
    for iteration in range(m.maxIterations):
        max_diff = 0.0
        for i in range(n):
            # Summation of A[i][j] * x_old[j] for j != i
            sigma = sum(m.mat[i][j] * x[j] for j in range(n) if i != j)
            
            if abs(m.mat[i][i]) < 1e-18:
                raise RuntimeError("Zero diagonal element detected in Jacobi.")
            
            # x_new[i] = (B[i] - sigma) / A[i][i]
            x_new[i] = (m.mat[i][n] - sigma) / m.mat[i][i]
            max_diff = max(max_diff, abs(x_new[i] - x[i]))
        
        x = list(x_new) # Synchronous update
        
        if max_diff < m.tolerance:
            print(f"Jacobi converged after {iteration + 1} iterations.")
            m.solution_vec = x
            return x
            
    print("Warning: Jacobi reached max iterations without full convergence.")
    m.solution_vec = x
    return x

def solve_gauss_seidel(m):
    """
    Solves Ax = B using the Gauss-Seidel method.
    Unlike Jacobi, Gauss-Seidel uses the newly calculated values of x[i] 
    as soon as they are available within the same iteration.
    """
    n = m.rows
    x = [0.0] * n
    
    print(f"Starting Gauss-Seidel iterations (max: {m.maxIterations}, tol: {m.tolerance})...")
    
    for iteration in range(m.maxIterations):
        max_diff = 0.0
        for i in range(n):
            old_xi = x[i]
            # Uses updated values for j < i and old values for j > i
            sigma = sum(m.mat[i][j] * x[j] for j in range(n) if i != j)
            
            if abs(m.mat[i][i]) < 1e-18:
                raise RuntimeError("Zero diagonal element detected in Gauss-Seidel.")
                
            x[i] = (m.mat[i][n] - sigma) / m.mat[i][i]
            max_diff = max(max_diff, abs(x[i] - old_xi))
            
        if max_diff < m.tolerance:
            print(f"Gauss-Seidel converged after {iteration + 1} iterations.")
            m.solution_vec = x
            return x
            
    print("Warning: Gauss-Seidel reached max iterations without full convergence.")
    m.solution_vec = x
    return x

def solve_sor(m, omega):
    """
    Solves Ax = B using Successive Over-Relaxation (SOR).
    SOR is a variant of Gauss-Seidel that uses a relaxation factor (omega).
    - 0 < omega < 1: Under-relaxation (for non-convergent systems).
    - 1 < omega < 2: Over-relaxation (to accelerate convergence).
    """
    n = m.rows
    x = [0.0] * n
    
    print(f"Starting SOR iterations (omega={omega}, max: {m.maxIterations})...")
    
    for iteration in range(m.maxIterations):
        max_diff = 0.0
        for i in range(n):
            old_xi = x[i]
            sigma = sum(m.mat[i][j] * x[j] for j in range(n) if i != j)
            
            if abs(m.mat[i][i]) < 1e-18:
                raise RuntimeError("Zero diagonal element detected in SOR.")
            
            # GS step
            x_gs = (m.mat[i][n] - sigma) / m.mat[i][i]
            
            # Weighted average with previous value
            x[i] = (1 - omega) * old_xi + omega * x_gs
            
            max_diff = max(max_diff, abs(x[i] - old_xi))
            
        if max_diff < m.tolerance:
            print(f"SOR converged after {iteration + 1} iterations.")
            m.solution_vec = x
            return x
            
    print("Warning: SOR reached max iterations.")
    m.solution_vec = x
    return x

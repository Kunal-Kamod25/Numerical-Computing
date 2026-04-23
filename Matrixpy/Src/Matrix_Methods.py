def read_from_file(m, filename):
    """
    Loads matrix data from a text file.
    If the matrix m has 0 rows/cols, the function attempts to infer the size:
    - If total elements is even, assumes it's an n x 2 (data points) matrix.
    - Otherwise, assumes a square n x n matrix.
    
    Args:
        m: The Matrix object to populate.
        filename (str): Path to the input file.
    """
    try:
        with open(filename, 'r') as f:
            # Skip empty lines and comments
            lines = [line.strip() for line in f if line.strip() and not line.strip().startswith('#')]
            data = []
            for line in lines:
                data.extend(line.split())
            
            if m.rows == 0 or m.cols == 0:
                total = len(data)
                if total % 2 == 0:
                    m.rows = total // 2
                    m.cols = 2
                else:
                    m.rows = int(total**0.5)
                    m.cols = m.rows
                m.mat = [[0.0] * m.cols for _ in range(m.rows)]
            else:
                expected = m.rows * m.cols
                if len(data) != expected:
                    raise ValueError(f"File data size ({len(data)} elements) does not match the expected matrix size ({m.rows}x{m.cols} = {expected} elements).")
            
            idx = 0
            for i in range(m.rows):
                for j in range(m.cols):
                    if idx < len(data):
                        m.mat[i][j] = float(data[idx])
                        idx += 1
    except Exception as e:
        raise RuntimeError(f"Error reading matrix from file: {e}")

def add_matrices(m1, m2):
    """Returns a new Matrix containing the element-wise sum of m1 and m2."""
    if m1.rows != m2.rows or m1.cols != m2.cols:
        raise ValueError("Matrix size mismatch for addition.")
    from Matrixpy.Include.matrix import Matrix
    result = Matrix(m1.rows, m1.cols)
    for i in range(m1.rows):
        for j in range(m1.cols):
            result.mat[i][j] = m1.mat[i][j] + m2.mat[i][j]
    return result

def subtract_matrices(m1, m2):
    """Returns a new Matrix containing the element-wise difference (m1 - m2)."""
    if m1.rows != m2.rows or m1.cols != m2.cols:
        raise ValueError("Matrix size mismatch for subtraction.")
    from Matrixpy.Include.matrix import Matrix
    result = Matrix(m1.rows, m1.cols)
    for i in range(m1.rows):
        for j in range(m1.cols):
            result.mat[i][j] = m1.mat[i][j] - m2.mat[i][j]
    return result

def multiply_matrices(m1, m2):
    """
    Performs standard row-column matrix multiplication.
    Complexity: O(rows * cols * common_dim).
    """
    if m1.cols != m2.rows:
        raise ValueError("Matrix size mismatch for multiplication.")
    from Matrixpy.Include.matrix import Matrix
    result = Matrix(m1.rows, m2.cols)
    for i in range(m1.rows):
        for j in range(m2.cols):
            sum_val = 0.0
            for k in range(m1.cols):
                sum_val += m1.mat[i][k] * m2.mat[k][j]
            result.mat[i][j] = sum_val
    return result

def divide_matrices(m1, m2):
    """Returns a new Matrix containing the element-wise quotient (m1 / m2)."""
    if m1.rows != m2.rows or m1.cols != m2.cols:
        raise ValueError("Matrix size mismatch for division.")
    from Matrixpy.Include.matrix import Matrix
    result = Matrix(m1.rows, m1.cols)
    for i in range(m1.rows):
        for j in range(m1.cols):
            if abs(m2.mat[i][j]) < 1e-18:
                raise RuntimeError("Division by zero in element-wise operator.")
            result.mat[i][j] = m1.mat[i][j] / m2.mat[i][j]
    return result

def is_symmetric(m):
    """Checks if A[i][j] == A[j][i] for all i, j."""
    if not m.isSquare(): return False
    for i in range(m.rows):
        for j in range(i):
            if abs(m.mat[i][j] - m.mat[j][i]) > 1e-18: return False
    return True

def is_identity(m):
    """Checks if diagonal is all 1s and off-diagonal is all 0s."""
    if not m.isSquare(): return False
    for i in range(m.rows):
        for j in range(m.cols):
            if i == j and abs(m.mat[i][j] - 1.0) > 1e-15: return False
            if i != j and abs(m.mat[i][j]) > 1e-15: return False
    return True

def is_diagonal(m):
    """Checks if all elements outside the main diagonal are zero."""
    if not m.isSquare(): return False
    for i in range(m.rows):
        for j in range(m.cols):
            if i != j and abs(m.mat[i][j]) > 1e-18: return False
    return True

def is_diagonally_dominant(m):
    """Checks the condition: |A[i][i]| >= sum(|A[i][j]|) for all j != i."""
    for i in range(m.rows):
        sum_val = sum(abs(m.mat[i][j]) for j in range(m.cols) if i != j)
        if abs(m.mat[i][i]) < sum_val: return False
    return True

def make_diagonally_dominant(m):
    """
    Attempts to make the matrix diagonally dominant by swapping rows.
    Useful for ensuring convergence in Jacobi and Gauss-Seidel methods.
    """
    n = m.rows
    for i in range(n):
        max_row = i
        max_val = abs(m.mat[i][i])
        for k in range(i + 1, n):
            if abs(m.mat[k][i]) > max_val:
                max_val = abs(m.mat[k][i])
                max_row = k
        if max_row != i:
            m.mat[i], m.mat[max_row] = m.mat[max_row], m.mat[i]

def display_properties(m):
    """Prints a formatted summary of matrix characteristics."""
    print("\n--- Matrix Properties ---")
    print(f"Symmetric Matrix:           {'yes' if is_symmetric(m) else 'no'}")
    print(f"Square Matrix:              {'yes' if m.isSquare() else 'no'}")
    print(f"Diagonal Matrix:            {'yes' if is_diagonal(m) else 'no'}")
    print(f"Identity Matrix:            {'yes' if is_identity(m) else 'no'}")
    print(f"Diagonally Dominant Matrix: {'yes' if is_diagonally_dominant(m) else 'no'}")
    print("-------------------------")

from Include.matrix import Matrix

def display_matrix(m):
    print(f"Matrix ({m.rows}x{m.cols}):")
    for row in m.mat:
        print("  " + "  ".join(f"{val:8.4f}" for val in row))

def add_matrices(m1, m2):
    if m1.rows != m2.rows or m1.cols != m2.cols:
        raise ValueError("Matrix dimensions must match for addition")
    
    result = Matrix(m1.rows, m1.cols)
    for i in range(m1.rows):
        for j in range(m1.cols):
            result.set(i, j, m1.get(i, j) + m2.get(i, j))
    return result

def multiply_matrices(m1, m2):
    if m1.cols != m2.rows:
        raise ValueError("Matrix 1 columns must match Matrix 2 rows for multiplication")
    
    result = Matrix(m1.rows, m2.cols)
    for i in range(m1.rows):
        for j in range(m2.cols):
            sum_val = 0
            for k in range(m1.cols):
                sum_val += m1.get(i, k) * m2.get(k, j)
            result.set(i, j, sum_val)
    return result
//k

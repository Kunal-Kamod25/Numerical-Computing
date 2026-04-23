def set_data(m, x, y):
    """
    Sets the coordinate points for interpolation.
    Points are stored as an n x 2 matrix (mat[i][0] = x, mat[i][1] = y).
    """
    if len(x) != len(y) or not x:
        raise ValueError("Interpolation data must be non-empty and x/y sizes must match.")
    
    # Mathematical constraint: Each x must map to exactly one y
    if len(set(x)) != len(x):
        raise ValueError("Interpolation x-values must be unique.")
        
    m.rows = len(x)
    m.cols = 2
    m.mat = [[0.0, 0.0] for _ in range(m.rows)]
    for i in range(m.rows):
        m.mat[i][0] = float(x[i])
        m.mat[i][1] = float(y[i])

def evaluate_lagrange(m, x):
    """
    Evaluates the Lagrange interpolating polynomial at point x.
    Formula: L(x) = sum_{i=0}^n y_i * l_i(x)
    where l_i(x) = product_{j=0, j!=i}^n (x - x_j) / (x_i - x_j)
    """
    if m.rows <= 0:
        raise RuntimeError("No interpolation data is set.")
        
    result = 0.0
    for i in range(m.rows):
        # Calculate the Lagrange basis polynomial l_i(x)
        basis = 1.0
        for j in range(m.rows):
            if i == j:
                continue
            
            den = m.mat[i][0] - m.mat[j][0]
            if abs(den) < 1e-18:
                raise RuntimeError("Duplicate x-values found during evaluation.")
                
            basis *= (x - m.mat[j][0]) / den
            
        result += m.mat[i][1] * basis
        
    return result

def evaluate_range_lagrange(m, xMin, xMax, samples):
    """
    Generates a list of (x, y) tuples representing the interpolated curve over a range.
    Useful for plotting the polynomial.
    """
    if samples < 2:
        raise ValueError("samples must be >= 2")
        
    curve = []
    step = (xMax - xMin) / (samples - 1)
    for i in range(samples):
        x = xMin + i * step
        curve.append((x, m.evaluate(x)))
        
    return curve

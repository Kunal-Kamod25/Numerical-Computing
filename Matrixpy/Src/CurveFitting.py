import math

def set_data(m, x, y):
    """
    Sets the data points for curve fitting.
    Stored as an n x 2 matrix where mat[i][0] = x_i and mat[i][1] = y_i.
    """
    if len(x) != len(y) or not x:
        raise ValueError("Curve fitting data must be non-empty and x/y sizes must match.")
    m.rows = len(x)
    m.cols = 2
    m.mat = [[0.0, 0.0] for _ in range(m.rows)]
    for i in range(m.rows):
        m.mat[i][0] = float(x[i])
        m.mat[i][1] = float(y[i])

def fit_least_squares(m):
    """
    Performs Linear Least Squares fitting (y = ax + b).
    Derived from minimizing the sum of squared residuals: S = sum(y_i - (ax_i + b))^2.
    
    Normal Equations:
    1. a * sum(x^2) + b * sum(x) = sum(xy)
    2. a * sum(x)   + b * n      = sum(y)
    """
    n = m.rows
    sum_x = 0.0
    sum_y = 0.0
    sum_xx = 0.0
    sum_xy = 0.0
    
    for i in range(n):
        xi = m.mat[i][0]
        yi = m.mat[i][1]
        sum_x += xi
        sum_y += yi
        sum_xx += xi * xi
        sum_xy += xi * yi
    
    # Using Cramer's rule for a 2x2 system:
    # [ sum_xx  sum_x ] [ a ] = [ sum_xy ]
    # [ sum_x   n     ] [ b ]   [ sum_y  ]
    
    denominator = n * sum_xx - sum_x * sum_x
    if abs(denominator) < 1e-18:
        raise RuntimeError("Singular system in Least Squares (e.g., all x-values are the same).")
        
    m.a = (n * sum_xy - sum_x * sum_y) / denominator
    m.b = (sum_y * sum_xx - sum_x * sum_xy) / denominator

def evaluate_least_squares(m, x):
    """Evaluates the fitted linear model at point x."""
    return m.a * x + m.b

def rms_least_squares(m):
    """
    Calculates the Root Mean Square (RMS) Error.
    RMS = sqrt( (1/n) * sum( (y_actual - y_fitted)^2 ) )
    """
    n = m.rows
    sum_sq_err = 0.0
    for i in range(n):
        err = (m.a * m.mat[i][0] + m.b) - m.mat[i][1]
        sum_sq_err += err * err
    return math.sqrt(sum_sq_err / n)

def evaluate_range_curve(m, xMin, xMax, samples):
    """Generates (x, y) coordinates for the fitted line over a range."""
    if samples < 2:
        raise ValueError("samples must be >= 2")
    curve = []
    step = (xMax - xMin) / (samples - 1)
    for i in range(samples):
        x = xMin + i * step
        curve.append((x, m.evaluate(x)))
    return curve

def print_report_least_squares(m):
    """Prints a summary of the fitting results."""
    print("\n--- Least Squares Fitting Report ---")
    print(f"Points fitted: {m.rows}")
    print(f"Linear model:  y = {m.a:.6f}x + {m.b:.6f}")
    print(f"RMS Error:     {m.rms():.8f}")
    print("------------------------------------\n")

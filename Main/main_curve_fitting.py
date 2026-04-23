"""
Least Squares Curve Fitting Demo
--------------------------------
Performs a linear regression (y = ax + b) on a set of noisy data points using 
the method of Least Squares. Includes statistical reporting (RMS Error) and 
automated plotting of the regression line.
"""

from Matrixpy.Include.curve_fitting import LeastSquares
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Least Squares Curve Fitting (Root Entry Point)")
    
    # --- Step 1: Data Loading & Model Fitting ---
    # Load points from file and solve the normal equations to find slope (a) and intercept (b).
    output_dir = ensure_output_dir("CurveFitting")
    input_file = choose_input_file("CurveFitting")
    print(f"Loading data from: {input_file}")
    
    ls = LeastSquares()
    ls.readFromFile(input_file)
    ls.fit() # Minimizes sum of squared residuals
    ls.printReport()
    
    x_data = ls.getXi()
    y_data = ls.getFi()
    
    # --- Step 2: Model Evaluation ---
    # Generate points along the fitted line for visualization.
    x_min, x_max = min(x_data), max(x_data)
    curve = ls.evaluateRange(x_min, x_max, 100)
    
    # --- Step 3: Result Persistence ---
    # Save the original noisy data and the smooth fitted line.
    data_file = os.path.join(output_dir, "fitting_points.dat")
    curve_file = os.path.join(output_dir, "fitted_line.dat")
    
    with open(data_file, 'w') as f:
        for xi, yi in zip(x_data, y_data): f.write(f"{xi} {yi}\n")
    
    with open(curve_file, 'w') as f:
        for px, py in curve: f.write(f"{px} {py}\n")
        
    # --- Step 4: Automated Visualization ---
    # Generate a plot showing the data points scattered around the best-fit line.
    generate_gnuplot_script(
        "curve_fit",
        curve_file,
        "graph_curve_fit.png",
        "Least Squares Linear Fit",
        "X", "Y",
        f"plot '{curve_file}' with lines lw 2 lc rgb 'red' title 'Fitted Line: y={ls.a:.4f}x+{ls.b:.4f}', \\\n"
        f"     '{data_file}' with points pt 7 ps 1.2 lc rgb 'blue' title 'Data Points'"
    )

if __name__ == "__main__":
    main()

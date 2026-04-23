"""
Lagrange Interpolation Demo
--------------------------
Calculates a unique polynomial that passes through a given set of data points.
The demo loads points from a file, evaluates the polynomial over a continuous 
range, and generates a plot to verify the fit.
"""

from Matrixpy.Include.interpolation import Lagrange
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Lagrange Interpolation (Root Entry Point)")
    
    # --- Step 1: Data Loading ---
    # Load (x, y) coordinates from the user-selected file.
    output_dir = ensure_output_dir("Interpolation")
    input_file = choose_input_file("Interpolation")
    print(f"Loading points from: {input_file}")
    
    lag = Lagrange()
    lag.readFromFile(input_file)
    
    x_data = lag.getX()
    y_data = lag.getY()
    
    # --- Step 2: Numerical Evaluation ---
    # Evaluate the Lagrange polynomial across the entire span of the input data.
    # We use 50 samples to ensure a smooth curve for visualization.
    print(f"\nEvaluating curve from x={x_data[0]} to x={x_data[-1]}...")
    curve = lag.evaluateRange(x_data[0], x_data[-1], 50)
    
    # --- Step 3: Result Persistence ---
    # Save both the original points and the generated curve for plotting.
    points_file = os.path.join(output_dir, "interp_points.dat")
    curve_file = os.path.join(output_dir, "lagrange_curve.dat")
    
    with open(points_file, 'w') as f:
        for xi, yi in zip(x_data, y_data): f.write(f"{xi} {yi}\n")
    
    with open(curve_file, 'w') as f:
        for px, py in curve: f.write(f"{px} {py}\n")
        
    # --- Step 4: Visualization ---
    # Automated Gnuplot generation.
    generate_gnuplot_script(
        "lagrange",
        curve_file,
        "graph_lagrange.png",
        "Lagrange Interpolation",
        "X", "Y",
        f"plot '{curve_file}' with lines lw 2 title 'Interpolated Curve', \\\n"
        f"     '{points_file}' with points pt 7 ps 1.5 title 'Data Points'"
    )

if __name__ == "__main__":
    main()

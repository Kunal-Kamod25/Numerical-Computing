from Matrixpy.Include.curve_fitting import LeastSquares
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Least Squares Curve Fitting Demo")
    
    # Setup Output
    output_dir = ensure_output_dir("CurveFitting")
    
    # 1. Initialization from File
    input_file = choose_input_file("CurveFitting")
    print(f"Loading data from: {input_file}")
    
    ls = LeastSquares()
    ls.readFromFile(input_file)
    ls.fit()
    ls.printReport()
    
    x_data = ls.getXi()
    y_data = ls.getFi()
    
    # 3. Range Evaluation
    x_min, x_max = min(x_data), max(x_data)
    print(f"\n3. Range Evaluation (x from {x_min} to {x_max}, 100 samples):")
    curve = ls.evaluateRange(x_min, x_max, 100)
    
    # 4. Save and Plot
    data_file = os.path.join(output_dir, "fitting_points.dat")
    curve_file = os.path.join(output_dir, "fitted_line.dat")
    
    with open(data_file, 'w') as f:
        for xi, yi in zip(x_data, y_data): f.write(f"{xi} {yi}\n")
    
    with open(curve_file, 'w') as f:
        for px, py in curve: f.write(f"{px} {py}\n")
        
    print(f"\nFiles saved to {output_dir}")
    
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

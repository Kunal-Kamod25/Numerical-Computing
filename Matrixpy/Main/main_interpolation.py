from Matrixpy.Include.interpolation import Lagrange
from Matrixpy.Src.File_Utils import choose_input_file, ensure_output_dir
from Matrixpy.Src.Plotting import generate_gnuplot_script
import os

def main():
    print("Lagrange Interpolation Demo")
    
    # Setup Output
    output_dir = ensure_output_dir("Interpolation")
    
    # 1. Initialization from File
    input_file = choose_input_file("Interpolation")
    print(f"Loading points from: {input_file}")
    
    lag = Lagrange() # Auto-sizes via smart readFromFile
    lag.readFromFile(input_file)
    
    x_data = lag.getX()
    y_data = lag.getY()
    
    # Test point evaluation
    test_x = 2.5
    expected_y = test_x ** 2
    calculated_y = lag.evaluate(test_x)
    
    # 3. Range Evaluation
    print(f"\n3. Range Evaluation (x from {x_data[0]} to {x_data[-1]}, 50 samples):")
    curve = lag.evaluateRange(x_data[0], x_data[-1], 50)
    
    # 4. Verify points themselves
    print("\n4. Verifying original points:")
    for xi in x_data:
        yi_calc = lag.evaluate(xi)
        print(f"   x: {xi} | Calculated y: {yi_calc:7.4f}")
    
    # 5. Save and Plot
    points_file = os.path.join(output_dir, "interp_points.dat")
    curve_file = os.path.join(output_dir, "lagrange_curve.dat")
    
    with open(points_file, 'w') as f:
        for xi, yi in zip(x_data, y_data): f.write(f"{xi} {yi}\n")
    
    with open(curve_file, 'w') as f:
        for px, py in curve: f.write(f"{px} {py}\n")
        
    print(f"\nFiles saved to {output_dir}")
    
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

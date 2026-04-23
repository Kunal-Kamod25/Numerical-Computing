import os

def generate_gnuplot_script(name, data_file, output_image, title, xlabel, ylabel, plot_cmd):
    """
    Automates the creation of Gnuplot scripts for visualizing numerical data.
    
    Args:
        name (str): Short identifier for the script (e.g., 'lu').
        data_file (str): Path to the .dat file containing the raw results.
        output_image (str): Filename for the resulting PNG image.
        title (str): Graph title.
        xlabel (str): X-axis label.
        ylabel (str): Y-axis label.
        plot_cmd (str): The specific gnuplot 'plot' command string.
    """
    plots_dir = os.path.join("Matrixpy", "Plots", "gnu_scripts")
    if not os.path.exists(plots_dir):
        os.makedirs(plots_dir)
        
    script_path = os.path.join(plots_dir, f"plot_{name}.gnu")
    
    # Ensure images directory exists
    img_dir = os.path.join("Matrixpy", "Plots", "images")
    if not os.path.exists(img_dir):
        os.makedirs(img_dir)
    
    content = f"""# Gnuplot script for {title}
set terminal pngcairo size 1280,720 enhanced font 'Arial,12'
set output 'Matrixpy/Plots/images/{output_image}'

set title "{title}"
set xlabel "{xlabel}"
set ylabel "{ylabel}"
set grid
set key left top

{plot_cmd}
"""
    with open(script_path, 'w') as f:
        f.write(content)
    
    print(f"Generated Gnuplot script: {script_path}")
    print(f"To plot, run: gnuplot {script_path}")
    return script_path

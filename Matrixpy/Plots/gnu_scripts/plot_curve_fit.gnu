# Gnuplot script for Least Squares Linear Fit
set terminal pngcairo size 1280,720 enhanced font 'Arial,12'
set output 'Matrixpy/Plots/images/graph_curve_fit.png'

set title "Least Squares Linear Fit"
set xlabel "X"
set ylabel "Y"
set grid
set key left top

plot 'Matrixpy\Outputs\CurveFitting\fitted_line.dat' with lines lw 2 lc rgb 'red' title 'Fitted Line: y=2.0393x+0.1679', \
     'Matrixpy\Outputs\CurveFitting\fitting_points.dat' with points pt 7 ps 1.2 lc rgb 'blue' title 'Data Points'

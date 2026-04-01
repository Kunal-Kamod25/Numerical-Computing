set terminal pngcairo size 1280,720 enhanced font 'Arial,11'
set output 'graph_gauss_seidel.png'
set title 'Gauss-Seidel - 2D Plot (X vs Y)'
set xlabel 'X (Index)'
set ylabel 'Y (Solution Value)'
set grid
set key left top
plot 'solution_gauss_seidel.dat' using 1:2 with linespoints lw 2 pt 7 ps 0.6 title 'Gauss-Seidel'

set title "LU Decomposition Performance"
set xlabel "Matrix Size (n)"
set ylabel "Execution Time (seconds)"

set grid
set key left top

plot \
"lu_results.dat" using 1:2 with linespoints linewidth 2 title "Doolittle", \
"lu_results.dat" using 1:3 with linespoints linewidth 2 title "Crout", \
"lu_results.dat" using 1:4 with linespoints linewidth 2 title "Cholesky"

set title 'Solution of Linear System'
set xlabel 'Variable Index'
set ylabel 'Solution Value'
plot 'solution.dat' using 1:2 with linespoints
pause -1

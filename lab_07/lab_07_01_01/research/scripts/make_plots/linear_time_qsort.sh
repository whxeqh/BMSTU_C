#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_qsort.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировки mysort от разного количества элементов"

plot "research/data/qsort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "qsort, случайный порядок чисел в массиве", \
     "research/data/qsort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "qsort, обратный порядок чисел в массиве", \
     "research/data/qsort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "green" title "qsort, сортированный порядок чисел в массиве", \
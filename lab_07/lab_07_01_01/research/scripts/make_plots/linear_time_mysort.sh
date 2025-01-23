#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_mysort.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировки mysort от разного количества элементов"

plot "research/data/mysort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "mysort, случайный порядок чисел в массиве", \
     "research/data/mysort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "mysort, обратный порядок чисел в массиве", \
     "research/data/mysort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "green" title "mysort, сортированный порядок чисел в массиве", \
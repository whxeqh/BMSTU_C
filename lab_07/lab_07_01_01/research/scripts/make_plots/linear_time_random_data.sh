#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_random_data.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировок mysort и qsort от разного количества элементов. Случайная упорядоченность"

plot "research/data/mysort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "mysort, случайный порядок чисел в массиве", \
     "research/data/qsort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "qsort, случайный порядок чисел в массиве"
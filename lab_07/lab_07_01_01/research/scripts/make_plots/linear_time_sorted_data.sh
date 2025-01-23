#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_sorted_data.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировок mysort и qsort от количества элементов. Отсортированная упорядоченность"

plot "research/data/mysort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "mysort, отсортированный порядок чисел в массиве", \
     "research/data/qsort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "qsort, отсортированный порядок чисел в массиве"
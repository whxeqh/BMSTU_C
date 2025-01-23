#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_revesed_data.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировок mysort и qsort от разного количества элементов. Обратная упорядоченность"

plot "research/data/mysort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "mysort, обратный порядок чисел в массиве", \
     "research/data/qsort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "qsort, обратный порядок чисел в массиве"
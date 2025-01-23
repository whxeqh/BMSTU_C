#!/usr/bin/gnuplot -persist

reset
NO_ANIMATION = 1

set terminal svg size 800, 600
set output 'research/plots/linear_time_all_together_keys.svg'

set xlabel "Количество элементов, шт"
set ylabel "Время, мкс"
set grid
set title "График зависимости времени выполнения сортировок от количества элементов"

plot "research/data/mysort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "red" title "mysort, случайный порядок чисел в массиве", \
     "research/data/mysort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "blue" title "mysort, обратный порядок чисел в массиве", \
     "research/data/mysort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "green" title "mysort, сортированный порядок чисел в массиве", \
     "research/data/qsort/random_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "orange" title "qsort, случайный порядок чисел в массиве", \
     "research/data/qsort/reverse_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "purple" title "qsort, обратный порядок чисел в массиве", \
     "research/data/qsort/sorted_order/data.txt" using 1:2 with linespoints pt 9 lt rgb "cyan" title "qsort, сортированный порядок чисел в массиве"

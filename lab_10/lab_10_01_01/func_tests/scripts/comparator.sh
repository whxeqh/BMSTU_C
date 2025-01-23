#!/bin/bash

# Проверка существования файла 2
if [ ! -f "$2" ]; then
    exit 2
fi


#echo $1
#echo $2
#ech

#echo $output_a
#echo
#echo $output_b
#echo

if cmp -s "$1" "$2"; then
    exit 0  # Файлы одинаковые
else
    exit 1  # Файлы разные
fi

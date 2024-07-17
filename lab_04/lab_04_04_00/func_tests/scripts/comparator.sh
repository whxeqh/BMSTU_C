#!/bin/bash

if [ ! -f "$2" ]; then
    exit 2
fi

# Извлечение содержимого из файла 1
output_a=$(cat "$1")

# Извлечение содержимого из файла 2
output_b=$(cat "$2")

# Сравнение содержимого файлов
if [ "$output_a" != "$output_b" ]; then
    exit 1
fi

exit 0

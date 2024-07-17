#!/bin/bash

if [ ! -f "$2" ]; then
    exit 2
fi

# Извлечение содержимого после слова "Result:" из файла 1
output_a=$(grep -Po '(?<=Result: )[\s\S]+' "$1")

# Извлечение содержимого после слова "Result:" из файла 2
output_b=$(grep -Po '(?<=Result: )[\s\S]+' "$2")

# Сравнение содержимого файлов
if [ "$output_a" != "$output_b" ]; then
    exit 1
fi

exit 0

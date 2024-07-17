#!/bin/bash

if [ ! -f "$2" ]; then
    exit 2
fi

# Извлечение всех строк после слова "Result:" из файла 1
output_a=$(awk '/Result:/ {flag=1; next} flag' "$1")

# Извлечение всех строк после слова "Result:" из файла 2
output_b=$(awk '/Result:/ {flag=1; next} flag' "$2")

# Сравнение содержимого файлов
if [ "$output_a" != "$output_b" ]; then
    exit 1
fi

exit 0

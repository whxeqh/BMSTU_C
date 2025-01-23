#!/bin/bash

args_file=$1

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
output_file="$SCRIPT_DIR/../../out/out.txt"
app="$SCRIPT_DIR/../../app.exe"

# Определение expected_file на основе args_file
expected_file="${args_file/_args/_out}"

# Проверка, существует ли файл expected_file
if [ ! -f "$expected_file" ]; then
    echo "Expected output file '$expected_file' not found" >&2
    exit 2
fi

# Проверка, есть ли флаг "--valgrind" среди аргументов
use_valgrind=false
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        use_valgrind=true
        break
    fi
done

echo
echo "$args_file"
echo

# Чтение аргументов из файла в массив
read -r args < "$args_file"
eval set -- "$args"

if [ "$use_valgrind" = true ]; then
    valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" "$@"
else
    "$app" "$@"
fi 

if [ $? -ne 0 ]; then
    exit 1
fi

# Запуск компаратора
comparator="$SCRIPT_DIR/comparator.sh"
if [ ! -f "$comparator" ]; then
    echo "Comparator script '$comparator' not found" >&2
    exit 2
fi

"$comparator" "$output_file" "$expected_file"
if [ $? -ne 0 ]; then
    exit 1
fi

exit 0

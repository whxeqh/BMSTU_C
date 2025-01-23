#!/bin/bash

input_file=$1
expected_file=$2
args_file=$3

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
output_file="$SCRIPT_DIR/../../out/output.txt"
app="$SCRIPT_DIR/../../app.exe"

# Проверка, есть ли флаг "--valgrind" среди аргументов
use_valgrind=false
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        use_valgrind=true
        break
    fi
done

# Проверка, есть ли файл с аргументами
if [ -n "$args_file" ]; then
    # Чтение аргументов из файла в массив
    read -r args < "$args_file"
    eval set -- "$args"

    # Проверка, есть ли "output.txt" среди аргументов
    if echo "$@" | grep -q "output.txt"; then
        if [ "$use_valgrind" = true ]; then
            valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" "$@"
        else
            "$app" "$@"
        fi 
    else
        if [ "$use_valgrind" = true ]; then
            valgrind --leak-check=yes --show-error-list=yes --quite --error-exitcode=1 "$app" "$@" > "$output_file"
        else
            "$app" "$@" > "$output_file"
        fi
    fi

    if [ $? -ne 0 ]; then
        exit 1
    fi
else
    if [ "$use_valgrind" = true ]; then
        valgrind --leak-check=yes --show-error-list=yes --quite --error-exitcode=1 "$app" < "$input_file" > "$output_file"
    else
        "$app" < "$input_file" > "$output_file"
    fi

    if [ $? -ne 0 ]; then
        exit 1
    fi
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

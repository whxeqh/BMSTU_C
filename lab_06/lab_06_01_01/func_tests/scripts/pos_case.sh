#!/bin/bash

# Проверка аргументов командной строки
if [ $# -lt 2 ]; then
    echo "Usage: $0 input_file expected_file [args_file]" >&2
    exit 2
fi

input_file=$1
expected_file=$2
args_file=$3
# Проверка наличия входных файлов
if [ ! -f "$input_file" ]; then
    echo "Input file '$input_file' does not exist" >&2
    exit 2
fi

if [ ! -f "$expected_file" ]; then
    echo "Expected file '$expected_file' does not exist" >&2
    exit 2
fi

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
output_file="$SCRIPT_DIR/../../output.txt"
app="$SCRIPT_DIR/../../app.exe"

# Проверка наличия исполняемого файла приложения
if [ ! -f "$app" ]; then
    echo "Application '$app' not found" >&2
    exit 2
fi

# Проверка, есть ли файл с аргументами
if [ -n "$args_file" ]; then
         # Чтение аргументов из файла в массив
    read -r args < "$args_file"
    eval set -- "$args"

    # Запуск приложения с аргументами
    "$app" "$@" >"$output_file"
    
    if [ $? -ne 0 ]; then
        #echo "eqeq"
        exit 1
    fi
else
    "$app" < "$input_file" > "$output_file"
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

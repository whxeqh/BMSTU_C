#!/bin/bash

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Проверка аргументов командной строки
if [ $# -lt 1 ]; then
    echo "Usage: $0 input_file [args_file]" >&2
    exit 3
fi

input_file=$1
args_file=$2

# Проверка наличия входного файла
if [ ! -f "$input_file" ]; then
    echo "Input file '$input_file' does not exist" >&2
    exit 2
fi

# Получение абсолютного пути к приложению
app="$SCRIPT_DIR/../../app.exe"

# Проверка существования файла приложения
if [ ! -f "$app" ]; then
    echo "Application '$app' not found at $app" >&2
    exit 2
fi

# Проверка, есть ли файл с аргументами
if [ -n "$args_file" ] && [ -f "$args_file" ]; then
    # Чтение аргументов из файла
    read -r args < "$args_file"
    eval set -- "$args"
    
    # Запуск программы с аргументами и проверка кода возврата
    if ! "$app" "$@" < "$input_file" > /dev/null; then
        exit 0  # Ожидаемая ошибка, возврат 0
    else
        exit 1  # Программа успешно завершилась, что не ожидается
    fi
else
    # Запуск программы без аргументов и проверка кода возврата
    if ! "$app" < "$input_file" > /dev/null; then
        exit 0  # Ожидаемая ошибка, возврат 0
    else
        exit 1  # Программа успешно завершилась, что не ожидается
    fi
fi

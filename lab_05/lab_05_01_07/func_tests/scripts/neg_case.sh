#!/bin/bash

# Получаю путь к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Проверка наличия аргументов (хотя бы одного)
if [ $# -lt 1 ]; then
    echo "Usage: $0 input_file [args_file]" >&2
    exit 3
fi

input_file=$1
args_file=$2

# Проверка существования входного файла
if [ ! -f "$input_file" ]; then
    echo "Input file '$input_file' does not exist" >&2
    exit 2
fi

# Получаю абсолютный путь к файлу app.exe
app_path="$SCRIPT_DIR/../../app.exe"

# Проверка существования файла app.exe
if [ ! -f "$app_path" ]; then
    echo "app.exe not found at $app_path" >&2
    exit 2
fi

# Чтение аргументов из файла, если он существует
args=""
if [ -n "$args_file" ] && [ -f "$args_file" ]; then
    args=$(cat "$args_file")
fi

# Запуск программы с аргументами и перенаправление ввода и вывода
if ! "$app_path" $args < "$input_file" > /dev/null; then
    exit 0  # Ожидается ошибка, возвращаем ноль в случае неуспеха
fi

# Возврат ненулевого кода в случае успешного завершения (что не ожидается)
exit 1

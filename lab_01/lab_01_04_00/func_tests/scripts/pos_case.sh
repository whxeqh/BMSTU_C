#!/bin/bash

# Получаем путь к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Проверка наличия аргументов
if [ $# -ne 2 ]; then
    echo "Need 2 files to compare" >&2
    exit 3
fi

if [ ! -f "$1" ]; then
    echo "File '$1' does not exist" >&2
    exit 2
fi

if [ ! -f "$2" ]; then
    echo "File '$2' does not exist" >&2
    exit 2
fi

# Считывание аргументов
file_stream_in="$1"
file_stream_out_expect="$2"

# Получаем абсолютный путь к файлу app.exe
app_path="$SCRIPT_DIR/../../app.exe"

# Проверяем, существует ли файл app.exe
if [ ! -f "$app_path" ]; then
    echo "app.exe not found at $app_path" >&2
    exit 2
fi

# Получаем абсолютный путь к файлу comparator.sh
comparator_path="$SCRIPT_DIR/comparator.sh"

# Проверяем, существует ли файл comparator.sh
if [ ! -f "$comparator_path" ]; then
    echo "comparator.sh not found at $comparator_path" >&2
    exit 2
fi

# Запуск программы с входным файлом
if ! "$app_path" < "$file_stream_in" > current.txt; then
    exit 1
fi

# Запуск компаратора для сравнения вывода с эталонным файлом
if ! "$comparator_path" "$file_stream_out_expect" "current.txt"; then
    exit 1
fi

# Возврат нулевого кода в случае успешного завершения
exit 0

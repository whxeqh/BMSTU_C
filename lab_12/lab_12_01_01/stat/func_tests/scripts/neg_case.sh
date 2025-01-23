#!/bin/bash

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

input_file=$1
args_file=$2

# Получение абсолютного пути к приложению
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
if [ -n "$args_file" ] && [ -f "$args_file" ]; then
    # Чтение аргументов из файла
    read -r args < "$args_file"
    eval set -- "$args"

    # Запуск программы с аргументами и проверка кода возврата
    if [ "$use_valgrind" = true ]; then
        if ! valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" "$@" < "$input_file" > /dev/null; then
            exit 0  # Ожидаемая ошибка, возврат 0
        else
            exit 1  # Программа успешно завершилась, что не ожидается
        fi
    else
        if ! "$app" "$@" < "$input_file" > /dev/null; then
            exit 0  # Ожидаемая ошибка, возврат 0
        else
            exit 1  # Программа успешно завершилась, что не ожидается
        fi
    fi
else
    # Запуск программы без аргументов и проверка кода возврата
    if [ "$use_valgrind" = true ]; then
        if ! valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" < "$input_file" > /dev/null; then
            exit 0  # Ожидаемая ошибка, возврат 0
        else
            exit 1  # Программа успешно завершилась, что не ожидается
        fi
    else
        if ! "$app" < "$input_file" > /dev/null; then
            exit 0  # Ожидаемая ошибка, возврат 0
        else
            exit 1  # Программа успешно завершилась, что не ожидается
        fi
    fi
fi

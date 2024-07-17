#!/bin/bash

# Проверка аргументов командной строки
if [ $# -lt 2 ]; then
    echo "Usage: $0 input_file expected_file [args_file]" >&2
    exit 2
fi

input_file=$1
expected_file=$2
args_file=${3:-}

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

# Основная логика выполнения
if [ -n "$args_file" ]; then
    args=($(cat "$args_file"))
    binary_mode=false

    # Проверка, есть ли в аргументах бинарный файл
    for arg in "${args[@]}"; do
        if [[ $arg == *.bin ]]; then
            binary_mode=true
            bin_file=$arg
            if [[ $arg == *pos_*_in.bin ]]; then
                # Выполняем импорт данных
                "$app" import "$input_file" "$bin_file"
                #echo "we dont know"
                if [ $? -ne 0 ]; then
                    exit 1
                fi
            fi
        fi
    done

    # Запуск приложения
    if $binary_mode; then
        "$app" "${args[@]}" > "$output_file"
        if [ $? -ne 0 ]; then
            exit 1
        fi

        # Выполняем экспорт данных, если был бинарный файл
        if [ -n "$bin_file" ]; then
            "$app" export "$bin_file" "$output_file"
            if [ $? -ne 0 ]; then
                exit 1
            fi
        fi
    else
        "$app" ${args[@]} < "$input_file" > "$output_file"
        if [ $? -ne 0 ]; then
            echo "eqeq"
            exit 1
        fi
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

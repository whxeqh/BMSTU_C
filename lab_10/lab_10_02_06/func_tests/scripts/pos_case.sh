#!/bin/bash


args_file=$1

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
output_file="$SCRIPT_DIR/../../out/output.txt"
app="$SCRIPT_DIR/../../app.exe"

use_valgrind=false
input_file=""
expected_output_file=""
args_file=""
has_args_file=false

# Проверка, есть ли флаг "--valgrind" среди аргументов
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        use_valgrind=true
    elif [[ "$arg" == *_args.txt ]]; then
        args_file="$arg"
        has_args_file=true
    elif [[ "$arg" == *_in.txt ]]; then
        input_file="$arg"
    elif [[ "$arg" == *_out.txt ]]; then
        expected_output_file="$arg"
    fi
done

#echo
#echo "$args_file"
#echo

if [ "$has_args_file" == true ]; then
    # Если есть args файл
    if [ ! -f "$args_file" ]; then
        echo "Args file '$args_file' not found" >&2
        exit 2
    fi

    expected_output_file="${args_file/_args/_out}"
    # Проверка, существует ли файл expected_file
    if [ ! -f "$expected_output_file" ]; then
        echo "Expected output file '$expected_output_file' not found" >&2
        exit 2
    fi

    # Считывание аргументов из args файла
    read -r args < "$args_file"
    eval set -- "$args"
else
    # Если нет args файла, проверка наличия input.txt и output.txt
    if [ -z "$input_file" ] || [ -z "$output_file" ]; then
        echo "Input or Output file not found" >&2
        exit 2
    fi

    if [ ! -f "$input_file" ]; then
        echo "Input file '$input_file' not found" >&2
        exit 2
    fi

    #if [ ! -f "$output_file" ]; then
    #    echo "Output file '$output_file' not found" >&2
    #    exit 2
    #fi
fi

# Запуск приложения
if [ "$use_valgrind" == true ]; then
    if [ "$has_args_file" == true ]; then
        valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" "$@" > "$output_file"
    else
        valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" < "$input_file" > "$output_file"
    fi
else
    if [ "$has_args_file" == true ]; then
        "$app" "$@" > "$output_file"
    else
        "$app" < "$input_file" > "$output_file"
    fi
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

"$comparator" "$output_file" "$expected_output_file"
if [ $? -ne 0 ]; then
    exit 1
fi

exit 0

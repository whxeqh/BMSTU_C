#!/bin/bash

# Получение пути к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

args_file=$1

# Получение абсолютного пути к приложению
app="$SCRIPT_DIR/../../app.exe"

# Флаг для использования valgrind
use_valgrind=false
has_args_file=false
args_file=""
input_file=""
out_file="out/output.txt"

# Проверка, есть ли флаг "--valgrind" среди аргументов
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        use_valgrind=true
    elif [[ "$arg" == *_args.txt ]]; then
        args_file="$arg"
        has_args_file=true
    elif [[ "$arg" == *_in.txt ]]; then
        input_file="$arg"
    fi
done


# Проверка, существует ли args_file
if [ "$has_args_file" == true ]; then
    # Если есть args_file, то читаем аргументы из него
    read -r args < "$args_file"
    eval set -- "$args"
fi

# Функция для выполнения программы с обработкой ошибок
run_app() {
    if [ "$use_valgrind" = true ]; then
        # Запуск с valgrind
        if [ "$has_args_file" == true ]; then
            if ! valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" "$@"; then
                return 0  # Ожидаемая ошибка, возврат 0
            else
                return 1  # Программа успешно завершилась, что не ожидается
            fi
        else 
            if ! valgrind --leak-check=yes --show-error-list=yes --quiet --error-exitcode=1 "$app" < "$input_file" > "$out_file"; then
                return 0  # Ожидаемая ошибка, возврат 0
            else
                return 1  # Программа успешно завершилась, что не ожидается
            fi
        fi
    else
        if [ "$has_args_file" == true ]; then
            if ! "$app" "$@"; then
                return 0  # Ожидаемая ошибка, возврат 0
            else
                return 1  # Программа успешно завершилась, что не ожидается
            fi
        else 
            if ! "$app" < "$input_file" > "$out_file"; then
                return 0  # Ожидаемая ошибка, возврат 0
            else
                return 1  # Программа успешно завершилась, что не ожидается
            fi
        fi
    fi
}

# Вызов функции с аргументами
run_app "$@"
exit $?

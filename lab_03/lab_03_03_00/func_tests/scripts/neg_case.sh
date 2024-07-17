#!/bin/bash

# Получаем путь к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Проверка наличия аргументов
if [ ! -f "$1" ]; then
    echo "File '$1' does not exist" >&2
    exit 2
fi

# Считывание аргументов
file_stream_in="$1"

# Получаем абсолютный путь к файлу app.exe
app_path="$SCRIPT_DIR/../../app.exe"

# Проверяем, существует ли файл app.exe
if [ ! -f "$app_path" ]; then
    echo "app.exe not found at $app_path" >&2
    exit 2
fi

# Запуск программы с входным файлом и перенаправлением вывода в /dev/null
"$app_path" < "$file_stream_in" > /dev/null

# Проверка кода завершения программы
if "$app_path" < "$file_stream_in" > /dev/null; then
    exit 1
fi

# Возврат нулевого кода в случае успешного завершения
exit 0

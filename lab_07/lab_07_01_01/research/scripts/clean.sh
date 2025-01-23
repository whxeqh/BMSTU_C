#!/bin/bash

# Получаем директорию скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

if [ -d "$SCRIPT_DIR/../plots" ]; then
    rm -r "$SCRIPT_DIR/../plots"
fi

if [ -d "$SCRIPT_DIR/../data/" ]; then
    rm -r "$SCRIPT_DIR/../data/"
fi

if [ -d "$SCRIPT_DIR/../out/" ]; then
    rm -r "$SCRIPT_DIR/../out/"
fi

echo
echo "Текстовые файлы и графики удалены"
echo

exit 0

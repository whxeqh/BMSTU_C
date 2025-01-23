#!/bin/bash

echo
echo "Строю графики :)"
echo

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

mkdir -p "$SCRIPT_DIR/make_plots"

# Убираем кавычки вокруг переменной с шаблоном
for script in $SCRIPT_DIR/make_plots/*.sh; do
    gnuplot "$script"
done

echo
echo "Графики успешно построены!"
echo "Скорее переходи в папку research/plots/ и посмотри на них"

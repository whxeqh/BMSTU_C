#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Запускаю программы с каждым санитайзером
echo "========================"
echo "Running AddressSanitizer"
"$SCRIPT_DIR"/build_debug_asan.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh

echo
echo "======================="
echo "Running MemorySanitizer"
"$SCRIPT_DIR"/build_debug_msan.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh

echo
echo "==================================="
echo "Running UndefinedBehaviorSanitizer"
"$SCRIPT_DIR"/build_debug_ubsan.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh

echo "Cleaning files"
"$SCRIPT_DIR"/clean.sh

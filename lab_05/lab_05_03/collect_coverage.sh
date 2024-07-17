#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")


"$SCRIPT_DIR"/build_gcov.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh
echo 

gcov main.c
gcov errors.c 
gcov file_size.c
gcov func_sort.c
gcov input_output_file.c

exit 0

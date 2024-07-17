#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")


"$SCRIPT_DIR"/build_gcov.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh
echo 

gcov main.c
gcov file_size.c
gcov import_export.c
gcov student.c
gcov task_functions.c

exit 0

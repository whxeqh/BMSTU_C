#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")


"$SCRIPT_DIR"/build_gcov.sh
"$SCRIPT_DIR"/func_tests/scripts/func_tests.sh
echo 

gcov main.c
gcov calculations.c
gcov errors.c
gcov io.c

exit 0

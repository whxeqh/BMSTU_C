#!/bin/bash

files="./func_test/scripts/*.txt *.txt *.exe *.o *.out *.bin *.gc*"
data="./func_tests/data/*.bin"

for file in $files; do
    rm -f "$file"
done

for file in $data; do
    rm -f "$file"
done

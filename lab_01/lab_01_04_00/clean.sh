#!/bin/bash

files="./func_test/scripts/*.txt *.txt *.exe *.o *.out *.gc*"

for file in $files; do
    rm -f "$file"
done

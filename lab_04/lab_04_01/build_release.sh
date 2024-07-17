#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c my_str_functions.c
gcc -o app.exe main.o my_str_functions.o -lm
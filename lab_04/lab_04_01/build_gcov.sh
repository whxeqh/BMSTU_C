#!/bin/bash

gcc -std=c99 -coverage -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c my_str_functions.c
gcc --coverage -o app.exe my_str_functions.o main.o -lm

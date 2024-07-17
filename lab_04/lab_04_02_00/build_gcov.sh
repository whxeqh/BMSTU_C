#!/bin/bash

gcc -std=c99 -coverage -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c io.c errors.c string_functions.c
gcc --coverage -o app.exe io.o errors.o string_functions.o main.o -lm

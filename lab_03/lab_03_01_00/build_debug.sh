#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c -O0 -g3 main.c io.c errors.c calculations.c
gcc -o app.exe main.o io.o errors.o calculations.o -lm
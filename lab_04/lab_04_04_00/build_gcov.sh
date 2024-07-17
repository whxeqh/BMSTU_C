#!/bin/bash

gcc -std=c99 -coverage -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c io.c calculations.c
gcc --coverage -o app.exe io.o calculations.o main.o -lm

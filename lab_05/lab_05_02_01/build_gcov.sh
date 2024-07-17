#!/bin/bash

gcc -std=c99 -coverage -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c file_work.c
gcc --coverage -o app.exe main.o file_work.o -lm

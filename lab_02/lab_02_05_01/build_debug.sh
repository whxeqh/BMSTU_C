#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c -O0 -g3 main.c
gcc -o app.exe main.o -lm

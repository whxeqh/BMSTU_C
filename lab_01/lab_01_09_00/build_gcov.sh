#!/bin/bash

gcc -std=c99 -coverage -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -c -o main.o main.c -lm
gcc --coverage -o app.exe main.o -lm

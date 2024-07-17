#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c main.c file_work.c
gcc -o app.exe main.o file_work.o -lm
#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=address -c main.c my_str_functions.c
clang -fno-omit-frame-pointer -fsanitize=address -o app.exe main.o my_str_functions.o -lm
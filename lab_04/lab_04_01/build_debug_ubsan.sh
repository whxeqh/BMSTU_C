#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=undefined -c main.c my_str_functions.c
clang -fno-omit-frame-pointer -fsanitize=undefined -o app.exe main.o my_str_functions.o -lm
#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=address -c main.c io.c calculations.c
clang -fno-omit-frame-pointer -fsanitize=address -o app.exe main.o io.o calculations.o -lm
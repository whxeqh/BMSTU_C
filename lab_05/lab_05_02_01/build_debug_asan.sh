#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=address -c main.c file_work.c
clang -fno-omit-frame-pointer -fsanitize=address -o app.exe main.o file_work.o -lm
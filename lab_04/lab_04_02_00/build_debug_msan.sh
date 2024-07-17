#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=memory -fPIE -c main.c io.c errors.c string_functions.c
clang -fno-omit-frame-pointer -fsanitize=memory -pie -o app.exe main.o io.o errors.o string_functions.o -lm
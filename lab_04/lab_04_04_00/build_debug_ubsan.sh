#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=undefined -c main.c io.c calculations.c
clang -fno-omit-frame-pointer -fsanitize=undefined -o app.exe main.o io.o calculations.o -lm
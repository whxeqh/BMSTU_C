#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=undefined -c main.c io.c errors.c calculations.c
clang -fno-omit-frame-pointer -fsanitize=undefined -o app.exe main.o io.o errors.o calculations.o -lm
#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -g -fno-omit-frame-pointer -fsanitize=address -c main.c -o app.o
clang -fno-omit-frame-pointer -fsanitize=address -o app.exe app.o -lm -g
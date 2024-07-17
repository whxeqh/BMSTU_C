#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=address -c *.c
clang -fno-omit-frame-pointer -fsanitize=address -o app.exe *.o -lm
#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -g -fno-omit-frame-pointer -fsanitize=memory -fPIE -c *.c
clang -fno-omit-frame-pointer -fsanitize=memory -pie -o app.exe *.o -lm
#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -g -fno-omit-frame-pointer -fsanitize=memory -fPIE -c main.c  -o app.o
clang -fno-omit-frame-pointer -fsanitize=memory -pie -o app.exe app.o -lm
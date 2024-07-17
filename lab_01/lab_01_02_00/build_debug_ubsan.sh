#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -g -fno-omit-frame-pointer -fsanitize=undefined -c main.c  -o app.o
clang -fno-omit-frame-pointer -fsanitize=undefined -o app.exe app.o -lm
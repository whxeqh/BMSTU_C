#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c -O0 -g3 -DLOCAL_BUILD *.c
gcc -o app.exe *.o -lm

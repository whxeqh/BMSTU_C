#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -DLOCAL_BUILD -c *.c
gcc -o app.exe *.o -lm
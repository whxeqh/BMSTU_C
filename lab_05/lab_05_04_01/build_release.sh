#!/bin/bash

gcc -std=gnu99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -Wextra -Wvla -c *c
gcc -o app.exe *.o -lm
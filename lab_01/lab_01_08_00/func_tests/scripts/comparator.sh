#!/bin/bash

if [ "$#" -ne 2 ]; then
    exit 1
fi

file1="$1"
file2="$2"

if [ ! -f "$file1" ] || [ ! -f "$file2" ]; then
    exit 1
fi

index=$(grep -m 1 -aob 'Result: ' "$file1" | cut -d: -f1)

if [ -n "$index" ]; then
    content_file1=$(tail -c +$((index + 8)) "$file1" | tr -d '\r' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
else
    exit 1
fi

index=$(grep -m 1 -aob 'Result: ' "$file2" | cut -d: -f1)

if [ -n "$index" ]; then
    content_file2=$(tail -c +$((index + 8)) "$file2" | tr -d '\r' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
else
    exit 1
fi

if [ "$content_file1" = "$content_file2" ]; then
    exit 0
else
    exit 1
fi

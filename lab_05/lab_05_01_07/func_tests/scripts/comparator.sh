#!/bin/bash

if [ ! -f "$2" ]; then
    exit 2
fi

value_1=$(grep -oP "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)" "$1")
value_2=$(grep -oP "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)" "$2")

if [ "$value_1" != "$value_2" ]; then
    exit 1
fi
exit 0

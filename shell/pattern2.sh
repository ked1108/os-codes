#!/bin/bash
for ((i = 0; i < 5; i++)); do
    for ((j = 0; j <= 5-i-1; j++)); do
        echo -n "  "
    done
    for ((j = 0; j <= i; j++)); do
        echo -n "* "
    done
    for ((j = 1; j <= i; j++)); do
        echo -n "* "
    done
    echo ""
done

#!/bin/bash
reverse=0
x=0
n=$1
while [[ $n -gt 0 ]]; do
    x=$((n%10))
    reverse=$((reverse*10+x))
    n=$((n/10))
done
echo "$reverse"

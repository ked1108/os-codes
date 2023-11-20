#!/bin/bash
string=$1
len=${#string}
reverse=""
for ((i = $len-1; i >= 0; i--)); do
    reverse="$reverse${string:$i:1}"
done
if [[ $reverse == $string ]]; then
    echo "Palindrome"
else
    echo "Not Palindrome"
fi

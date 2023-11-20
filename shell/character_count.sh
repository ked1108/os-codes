#!/bin/bash
input=$1
echo "$input" | grep -o .| uniq -c | while read -r line; 
do 
    count=$(echo "$line" | awk '{print $1}')
    char=$(echo "$line" | awk '{print $2}')
    echo "$char $count"
done


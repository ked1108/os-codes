#!/bin/bash
x=1
y=0
z=0
for ((i=0;i<$1;i++));
do 
    echo -n "$z "
    z=$((x+y))
    x=$y
    y=$z
done
echo ""

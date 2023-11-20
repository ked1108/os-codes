#!/bin/bash
input=$1
eur=$(echo "$input*0.91" | bc)
echo "EUR:   $eur"

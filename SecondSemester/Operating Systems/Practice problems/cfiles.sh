#!/bin/bash

count=0
for file in $(find "$1" -name "*.c"); do
    lines=$(wc -l < "$file")
    if (( lines > 1 )); then
        echo "$file has $lines lines"
        (( count++ ))
        if (( count >= 2 )); then
            break
        fi
    fi
done



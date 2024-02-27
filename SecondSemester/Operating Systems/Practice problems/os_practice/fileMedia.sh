#!/bin/bash

count=0
total=0

# Recursive function to traverse directories and calculate total count
traverse_directories() {
    local current_dir=$2

    # Loop through all files and directories in the current directory
    for file in "$current_dir"/*; do
        if [[ -f "$file" ]]; then
            # File found, check if it has .txt extension
            if [[ "$file" == *.txt ]]; then
                count=$((count + 1))
            fi
        elif [[ -d "$file" ]]; then
            # Directory found, recursively call the function
            traverse_directories "$file"
        fi
    done
}

# Calculate the total count
traverse_directories "$(pwd)"
total=$count

# Calculate the average
if [[ $total -gt 0 ]]; then
    average=$(bc -l <<< "$total / $count")
else
    average=0
fi

echo "Total number of .txt files: $total"
echo "Average number of .txt files: $average"


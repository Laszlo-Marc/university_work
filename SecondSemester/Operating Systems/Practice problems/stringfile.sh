#!/bin/bash

# Check if there are any command-line arguments
if [ $# -eq 0 ]; then
    echo "Error: no command-line arguments provided"
    exit 1
fi

# Loop over each pair of filename and string
for (i=1; i<=$#; i+=2) do
    filename="${!i}"
    string="${!((i+1))}"

    # Check if the file exists and is readable
    if [ ! -f "$filename" ] || [ ! -r "$filename" ]; then
        echo "Error: file $filename does not exist or is not readable"
        continue
    fi

    # Count the number of occurrences of the string in the file
    count=$(grep -o "$string" "$filename" | wc -l)

    # Check if the count is at least 3
    if [ $count -ge 3 ];then
        echo "$filename contains $string at least 3 times"
    fi
done


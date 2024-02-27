#!/bin/bash

# Define the directory to search in
directory=$1

# Find all files with write permissions for everyone and store their paths in an array
files=($(find "$directory" -type f -perm -o+w))

# Loop through the array and change the permissions of each file
for file in "${files[@]}"; do
    # Display the file name and permissions before the change
    echo "File name: $file"
    echo "Permissions before: $(stat -c %a "$file")"

    # Remove write permission for everyone
    chmod o-w "$file"

    # Display the permissions after the change
    echo "Permissions after: $(stat -c %a "$file")"
done



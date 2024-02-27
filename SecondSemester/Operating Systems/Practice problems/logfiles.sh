#!/bin/bash

for file in $(find "$1" -name "*.log"); do
	sort "$file" -o "$file"
done

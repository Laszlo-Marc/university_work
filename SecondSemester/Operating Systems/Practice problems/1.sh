#!/bin/bash

for arg; do
	if [ -z $arg ]; then
		echo "No parameters given"
		exit 1
	else
		users="$users,$arg"

	fi
done

while true; do
	ps -f -u $users | awk 'NR>1{print $1}' | sort | uniq -c
	sleep 1
done

#!/bin/bash
if [ $# -ne 1 ]; then
	echo "The script must receive a single argument"
	exit 1
fi

if [ ! -d $1 ]; then 
	echo "Argument must be a directory"
	exit 1
fi

for f in {find $1}; do
	if [ -f $f ]; then
		if $f | grep -q -E "C source"; then
			echo $f
		fi
	fi
done

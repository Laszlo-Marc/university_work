#!/bin/bash
if test $# == 0; then
	echo No arguments were given
	exit 
fi

while true; do
  for user in "$@"; do
     ps -eo $user = | sort | uniq -c
    echo "User $user has $(num_procs) processes."
  done
  sleep 1
done


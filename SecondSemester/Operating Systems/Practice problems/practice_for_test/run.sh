#!/bin/bash 

echo 0 > a.txt
./example_lecture.sh a.txt &
./example_lecture.sh a.txt &
./example_lecture.sh a.txt &

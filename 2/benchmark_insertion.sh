#!/bin/bash
# Arguments: 0 or 1 for insertion sort algorithm to compute times
TIMEFORMAT=%R
n=10
for f in {1..6} # Size
do
	echo $n
	for e in {1..10} # Repetitions to compute average time
	do
		time ./insertion $1 $n < "data/P2/benchmark/$n.txt"
	done
	n=$(($n*10))
done
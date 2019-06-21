#!/bin/bash
# Arguments: 0 or 1 for algorithm to compute times
TIMEFORMAT=%R
n=10
for f in {1..6} # Files
do
	echo $n
	for e in {1..10} # Repetitions to compute average time
	do
		time ./tarea2 $1 < "data/benchmark/input_1_$n.txt" &> /dev/null
	done
	n=$(($n*10))
done
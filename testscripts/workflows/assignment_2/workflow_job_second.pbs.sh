#!/bin/bash
#PBS -L tasks=1:lprocs=1:swap=1gb
#PBS -l walltime=2:00

cd "$PBS_O_WORKDIR"

# Read the input from the previous "simulation"
number=$(cat sim1.txt)
# Run the new "simulation" and write the result
echo $((2*$number)) >sim2.txt
sleep 30

#!/bin/bash
#PBS -L tasks=1:lprocs=1:swap=1gb
#PBS -l walltime=2:00

cd "$PBS_O_WORKDIR"

# Read the result from a previous simulation
number=$(cat sim2.txt)
# Apply the perturbation
number=$(($number+$perturbation))
# Run the "simulation" and write the result
echo $((2*$number)) >sim3_pert_$perturbation.txt
sleep 30

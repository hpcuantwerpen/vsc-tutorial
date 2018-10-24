#!/bin/bash
#PBS -L tasks=1:lprocs=1:swap=1gb
#PBS -l walltime=2:00

cd "$PBS_O_WORKDIR"

# Run the "simulation"
echo "10" >sim1.txt
sleep 30


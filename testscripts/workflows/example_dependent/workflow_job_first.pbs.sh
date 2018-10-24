#!/bin/bash
#PBS -L tasks=1:lprocs=1:swap=1gb
#PBS -l walltime=10:00

cd "$PBS_O_WORKDIR"

echo "10" >outputfile
sleep 30


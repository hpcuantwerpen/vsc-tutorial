#!/bin/bash
# Test the weather program
#PBS -L tasks=1:lprocs=1:swap=512mb
#PBS -l walltime=01:00:00

cd $PBS_O_WORKDIR
./weather -t 20 -p 1.05 -v 4.3

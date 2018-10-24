#!/bin/bash
# Example of a worker parameter sweep job
#
#PBS -L tasks=28:lprocs=1:swap=512mb
#PBS -l walltime=04:00:00

cd $PBS_O_WORKDIR
./weather -t $temperature -p $pressure -v $volume

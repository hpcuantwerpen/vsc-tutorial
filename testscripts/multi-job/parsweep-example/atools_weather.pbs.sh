#!/bin/bash
# Example of a worker parameter sweep job
#
#PBS -L tasks=1:lprocs=1:swap=512mb
#PBS -l walltime=10:00

ml calcua/supported
ml personal
ml atools/torque

cd $PBS_O_WORKDIR

source <(aenv --data data.csv)
./weather -t $temperature -p $pressure -v $volume

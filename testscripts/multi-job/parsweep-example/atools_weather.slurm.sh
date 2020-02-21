#!/bin/bash
# Example of a worker parameter sweep job
#
#SBATCH --ntasks=1 --cpus-per-task=1 --mem-per-cpu=512M
#SBATCH --time=10:00

ml calcua/supported
ml personal
ml atools/slurm

source <(aenv --data data.csv)
./weather -t $temperature -p $pressure -v $volume

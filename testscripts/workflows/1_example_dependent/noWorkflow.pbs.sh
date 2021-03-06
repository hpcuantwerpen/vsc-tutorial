#!/bin/bash
#PBS -L tasks=1:lprocs=1:swap=1gb
#PBS -l walltime=30:00

cd "$PBS_O_WORKDIR"

# Part 1
echo "10" >outputfile; sleep 30

# First perturbation, uses result of part 1
multiplier=5
mkdir mult-$multiplier ; pushd mult-$multiplier
number=$(cat ../outputfile)
echo $(($number*$multiplier)) >outputfile; sleep 30
popd

# Second perturbation, uses result of part 1
multiplier=10
mkdir mult-$multiplier ; pushd mult-$multiplier
number=$(cat ../outputfile)
echo $(($number*$multiplier)) >outputfile; sleep 30 


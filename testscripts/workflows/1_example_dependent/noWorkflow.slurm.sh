#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=10:00

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


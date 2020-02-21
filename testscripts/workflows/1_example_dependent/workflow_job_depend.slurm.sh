#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=2:00

mkdir mult-$multiplier ; cd mult-$multiplier
number=$(cat ../outputfile)
echo $(($number*$multiplier)) >outputfile
sleep 30

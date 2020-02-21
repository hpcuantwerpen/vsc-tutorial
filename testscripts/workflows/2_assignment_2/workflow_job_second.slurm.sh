#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=2:00

# Read the input from the previous "simulation"
number=$(cat sim1.txt)
# Run the new "simulation" and write the result
echo $((2*$number)) >sim2.txt
sleep 30

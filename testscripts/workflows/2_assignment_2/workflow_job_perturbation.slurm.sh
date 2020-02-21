#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=2:00

# Read the result from a previous simulation
number=$(cat sim2.txt)
# Apply the perturbation
number=$(($number+$perturbation))
# Run the "simulation" and write the result
echo $((2*$number)) >sim3_pert_$perturbation.txt
sleep 30

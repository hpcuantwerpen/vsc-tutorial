#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=2:00

# Run the "simulation"
echo "10" >sim1.txt
sleep 30


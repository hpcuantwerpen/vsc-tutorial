#!/bin/bash
#SBATCH --ntasks=1 --cpus-per-task=1 --mem=1g
#SBATCH --time=2:00

echo "10" >outputfile
sleep 30


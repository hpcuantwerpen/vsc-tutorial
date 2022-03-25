#! /bin/bash
#SBATCH --job-name=serial_check
#SBATCH --time=0:20
#SBATCH --partition=debug
#SBATCH --ntasks=1 --cpus-per-task=1
#SBATCH --output=%x-%j.out

module --force purge
ml calcua/2020a
ml intel/2020a

export OMP_PROC_BIND=true

../../bin/serial_check -l test -w 5 -n -r

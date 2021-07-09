#! /bin/bash
#SBATCH --time=2:00
#SBATCH --partition=debug
#SBATCH --ntasks=8 --cpus-per-task=1

module --force purge
ml calcua/2020a
ml intel/2020a

srun ../bin/hybrid_hello

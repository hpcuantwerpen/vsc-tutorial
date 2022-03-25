#! /bin/bash
#SBATCH --job-name=mpi_check
#SBATCH --time=0:20
#SBATCH --partition=debug
#SBATCH --ntasks=4 --cpus-per-task=1
#SBATCH --hint=nomultithread
#SBATCH --output=%x-%j.out

module --force purge
ml calcua/2020a
ml intel/2020a

export OMP_NUM_THREADS=1

srun ../../bin/mpi_check -l test -w 5 -n -r

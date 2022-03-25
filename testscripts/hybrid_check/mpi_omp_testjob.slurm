#! /bin/bash
#SBATCH --job-name=mpi_omp_check
#SBATCH --time=2:00
#SBATCH --partition=debug
#SBATCH --ntasks=4 --cpus-per-task=4
#SBATCH --hint=nomultithread
#SBATCH --output=%x-%j.out

module --force purge
ml calcua/2020a
ml intel/2020a

export OMP_PROC_BIND=true
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun ../../bin/mpi_omp_check -l test -w 5 -n -r

#! /bin/bash
#SBATCH --time=0:15
#SBATCH --partition=short
#SBATCH --ntasks=4 --cpus-per-task=4
#SBATCH hetjob
#SBATCH --partition=short
#SBATCH --ntasks=2 --cpus-per-task=8

module --force purge
ml calcua/2020a
ml intel/2020a

export OMP_PROC_BIND=true
srun --ntasks=4 --cpus-per-task=4 ../../bin/mpi_omp_check -l exe1 -w 5 -n -r : \
     --ntasks=2 --cpus-per-task=8 ../../bin/mpi_omp_check -l exe2

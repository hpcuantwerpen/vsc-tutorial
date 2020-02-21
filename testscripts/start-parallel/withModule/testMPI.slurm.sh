#! /bin/bash
#SBATCH --ntasks=40 --cpus-per-task=1 --mem-per-cpu=1g
#SBATCH --time=5:00
#SBATCH --job-name=MPI-hello-test

module purge
module load calcua/supported
module load vsc-tutorial/201810-intel-2018b

srun mpi_hello

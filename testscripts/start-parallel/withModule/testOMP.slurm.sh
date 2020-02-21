#! /bin/bash
#SBATCH --ntasks=1 --cpus-per-task=5 --mem=4g
#SBATCH--time=5:00
#SBATCH --job-name=omp-hello-test

module purge
module load calcua/supported
module load vsc-tutorial/201810-intel-2018b

# The next line doesn't seem to be needed with Slurm but is safe to add.
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

omp_hello

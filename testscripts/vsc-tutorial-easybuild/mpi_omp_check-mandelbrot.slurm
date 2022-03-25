#! /bin/bash
#SBATCH --job-name=mpi_omp_check-mandelbrot
#SBATCH --time=2:00
#SBATCH --partition=debug
#SBATCH --ntasks=4 --cpus-per-task=4
#SBATCH --hint=nomultithread
#SBATCH --output=%x-%j.out

module purge
module load calcua/2020a
module load intel/2020a
module load vsc-tutorial/202203-intel-2020a
module list

echo -e "\nJob name: $SLURM_JOB_NAME"
echo "Submitted from $SLURM_SUBMIT_HOST"
echo "Running on $SLURM_JOB_NODELIST"
echo -e "Running $SLURM_NTASKS tasks with $SLURM_CPUS_PER_TASK CPUs per task.\n"
egrep "^#SBATCH" $0
echo -e "\nTask set of the current shell:\n$(taskset -c -p $$)"
echo "Running taskset on all tasks via srun:"
srun bash -c 'echo "Task $SLURM_PROCID:  $(taskset -c -p $SLURM_TASK_PID)"' | sort

srun ../../bin/mpi_omp_check -l test -w 5 -n -r

echo -e "\n\n\nCheck: SLURM environment variables\n"
env | egrep ^SLURM

echo -e "\n\n\nJob script:\n"
cat $0

echo -e "\n\n\nRequest information using \"sacct -j $SLURM_JOB_ID -o JobID%14,AllocNodes,AllocCPUS\" (may be incomplete, check afterwards):\n"
egrep "^#SBATCH" $0
echo -e
sacct -j $SLURM_JOB_ID -o JobID%14,AllocNodes,AllocCPUS

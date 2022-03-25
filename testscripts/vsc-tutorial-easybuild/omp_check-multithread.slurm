#! /bin/bash
#SBATCH -J omp_check-multithread
#SBATCH -n 1
#SBATCH -c 4
#SBATCH -t 5:00
#SBATCH --hint=multithread
#SBATCH -o %x-%j.out

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

echo -e "\n1) No OMP variables.\n"
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n2) With OMP_PLACES=cores and OMP_PROC_BIND=true\n"
export OMP_PLACES=cores
export OMP_PROC_BIND=true
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n3) With OMP_PLACES=threads and OMP_PROC_BIND=true\n"
export OMP_PLACES=threads
export OMP_PROC_BIND=true
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n4) Without OMP_PLACES and OMP_PROC_BIND but with OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK.\n"
unset OMP_PLACES
unset OMP_PROC_BIND
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n5) With MP_PLACES=cores and OMP_PROC_BIND=true and OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK.\n"
export OMP_PLACES=cores
export OMP_PROC_BIND=true
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n6) With MP_PLACES=threads and OMP_PROC_BIND=true and OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK.\n"
export OMP_PLACES=threads
export OMP_PROC_BIND=true
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
env | egrep ^OMP_
echo -e "\n- Without srun\n"
omp_check -r
echo -e "\n- With srun\n"
srun omp_check -r

echo -e "\n\n\nCheck: SLURM environment variables\n"
env | egrep ^SLURM

echo -e "\n\n\nJob script:\n"
cat $0

echo -e "\n\n\nRequest information using \"sacct -j $SLURM_JOB_ID -o JobID%14,AllocNodes,AllocCPUS\" (may be incomplete, check afterwards):\n"
egrep "^#SBATCH" $0
echo -e
sacct -j $SLURM_JOB_ID -o JobID%14,AllocNodes,AllocCPUS

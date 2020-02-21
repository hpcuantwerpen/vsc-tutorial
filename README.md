[GitHub site: https://github.com/hpcuantwerpen/vsc-tutorial](https://github.com/hpcuantwerpen/vsc-tutorial)

# vsc-tutorial

This repository contains a number of programs/commands that are useful for the
hands-ion exercises during the HPC tutorial sessions at UAntwerp. They are meant
to be compiled into a module that can be loaded and used by the students, so all
commands are put in a bin directory and there are also man pages provided. 
We suggest to also copy the source files to illustrate various programming models
to those who might be interested.

## Example job scripts for omp_hello

omp_hello can be used to experiment with launching OpenMP jobs

### With Torque/Moab

```bash
#! /bin/bash
#PBS -L tasks=1:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N omp-hello-test

cd $PBS_O_WORKDIR

module load calcua/supported
module load vsc-tutorial/201810-intel-2018b
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
omp_hello
```

### With Slurm Workload manager

```bash
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
```

## Example job scripts for mpi_hello

mpi_hello is a program to experiment with launching MPI jobs

### With Torque/Moab

```bash
#! /bin/bash
#PBS -L tasks=2:lprocs=all:place=node:swap=4gb
#PBS -l walltime=5:00
#PBS -N MPI-hello-test

cd $PBS_O_WORKDIR

module load calcua/supported
module load vsc-tutorial/201810-intel-2018b
mpirun mpi_hello
```

### With Slurm Workload manager

```bash
#! /bin/bash
#SBATCH --ntasks=40 --cpus-per-task=1 --mem-per-cpu=1g
#SBATCH --time=5:00
#SBATCH --job-name=MPI-hello-test

module purge
module load calcua/supported
module load vsc-tutorial/201810-intel-2018b

srun mpi_hello
```

## Example job scripts for mpi_omp_hello

mpi_opm_hello is a program to experiment with launching hybrid
MPI/OpenMP jobs.

### With Torque/Moab

```bash
#! /bin/bash
#PBS -L tasks=8:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N hybrid-hello-test

cd $PBS_O_WORKDIR

module load calcua/supported
module load vsc-tutorial/201810-intel-2018b
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
torque-host-per-line >machinefile.$PBS_JOBID
mpirun -machinefile machinefile.$PBS_JOBID mpi_omp_hello
/bin/rm machinefile.$PBS_JOBID
```

### With Slurm Workload Manager

```bash
#! /bin/bash
#SBATCH --ntasks=8 --cpus-per-task=5 --mem-per-cpu=512m
#SBATCH --time=5:00
#SBATCH --job-name=hybrid-hello-test

module purge
module load calcua/supported
module load vsc-tutorial/201810-intel-2018b

# The next line doesn't seem to be needed with Slurm but is safe to add.
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun mpi_omp_hello
```

This directory contains a number of programs/commands that are useful for the
hands-ion exercises during the HPC tutorial sessions at UAntwerp. They are meant
to be compiled into a module that can be loaded and used by the students, so all
commands are put in a bin directory and there are also man pages provided. 
We suggest to also copy the source files to illustrate various programming models
to those who might be interested.

Example job script for omp_hello
================================

#! /bin/bash
#PBS -L tasks=1:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N omp-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load vsc-tutorial/201810-intel-2018b
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
omp_hello


Example job script for mpi_hello
================================

#! /bin/bash
#PBS -L tasks=2:lprocs=all:place=node:swap=4gb
#PBS -l walltime=5:00
#PBS -N MPI-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load vsc-tutorial/201810-intel-2018b
mpirun mpi_hello


Example job script for mpi_omp_hello
====================================

#! /bin/bash
#PBS -L tasks=8:lprocs=7:swap=4gb
#PBS -l walltime=5:00
#PBS -N hybrid-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load vsc-tutorial/201810-intel-2018b
module load torque-tools

export OMP_NUM_THREADS=$(torque-lprocs 0)
torque-host-per-line >machinefile.$PBS_JOBID
mpirun -machinefile machinefile.$PBS_JOBID mpi_omp_hello
/bin/rm machinefile.$PBS_JOBID


#! /bin/bash
#PBS -L tasks=2:lprocs=all:place=node:swap=4gb
#PBS -l walltime=5:00
#PBS -N MPI-hello-test

cd $PBS_O_WORKDIR

module load $VSC_INSTITUTE_CLUSTER/supported
module load vsc-tutorial/201810-intel-2018b
mpirun mpi_hello
